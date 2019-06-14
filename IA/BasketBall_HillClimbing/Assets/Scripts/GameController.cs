using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameController : MonoBehaviour
{   

    [SerializeField]
    Parameters bestValues;                     //Mejor valor
    public float bestScore;                    //Mejor resultado
    public float lastbestScore;                //Ultimo mejor resultado

    [SerializeField]
    int simulationsFinished = 0;               //Numero de simulaciones finalizadas
    public Field mainField;                    //Campo principal
    List<Field> fieldsToHill;                  //Campos base de las pruebas del Hill Climbing



    public Steps steps;                        //Steps base 
    public Steps currentSteps;                 //Steps actuales    
    List<Steps> allCurrentSteps;               //Steps que se aplicaran a todas las pruebas del Hill Climbing 
    

    bool onHill;                               //Está en modo de escalar?
    public float indexClimbing = 1.5f;         //Indice de escalado



    public GameObject prefab;
    public Vector3 windForce;                  //Vector dirección del viento     

    public static GameController instance;     //instancia del Controller 


    // Inicializamos todas las variables
    void Start()
    {

        //Steps
        steps = new Steps();
        fieldsToHill = new List<Field>();
        allCurrentSteps = new List<Steps>();
        GetFields();
        onHill = false;
        


        bestValues = new Parameters();
        lastbestScore = bestValues.distance;
        
        bestValues.RandomStart();                   //Generamos unos valores al azar
        mainField.originalParameters = bestValues;  //Seteamos al campo principal esos valores
        mainField.steps = steps;                    //Seteamos los steps iniciales al campo principal
        

        if (!GameController.instance)
            instance = this;
        else
            Destroy(this);

        StartSimulation();
        
    }

    // Update is called once per frame
    void Update()
    {
        if (indexClimbing >= 20)//Los valores serán demasiado grandes, asi que devolvemos los steps a su origen.
        {
            steps = new Steps();
            indexClimbing = 1.5f;
        }
            
        if (onHill)//Si está escalando
        {
            if(simulationsFinished >= fieldsToHill.Count && mainField.hasFinished) //Si han terminado todos los campos
            {
                SimulationHasFinished();//Comprobamos mejor resultado
                if(lastbestScore == bestScore) //Nos hemos estancado
                {
                    indexClimbing += 0.5f;
                    HillClimbing(); //Actualizamos los steps
                    Debug.Log("Hemos llegado a un pico");
                    
                    onHill = true;
                    for (short i = 0; i < fieldsToHill.Count; ++i)//Seteamos los 27 campos
                    {

                        fieldsToHill[i].steps = allCurrentSteps[i];
                        fieldsToHill[i].originalParameters = bestValues;

                        fieldsToHill[i].StartSimulation();

                    }
                }
                else //Actulizamos los valores
                {
                    Debug.Log("Mejora");
                    onHill = false;
                    indexClimbing = 1.5f;
                    lastbestScore = bestScore;
                }

                StartSimulation();//Iniciamos el campo principal
                simulationsFinished = 0;

            }
        }
        else
        {
            if (mainField.hasFinished)
            {
                SimulationHasFinished();
                if (lastbestScore == bestScore)
                {
                    indexClimbing += 0.5f;
                    HillClimbing();
                    Debug.Log("Hemos llegado a un pico");
                    onHill = true;
                    for (short i = 0; i < fieldsToHill.Count; ++i)
                    {

                        fieldsToHill[i].steps = allCurrentSteps[i];
                        fieldsToHill[i].originalParameters = bestValues;
                        fieldsToHill[i].StartSimulation();

                    }


                }
                else
                {
                    Debug.Log("Mejora");
                    onHill = false;
                    lastbestScore = bestScore;
                }

                StartSimulation();
                simulationsFinished = 0;

            }

        }
      
    }

    //Destruye la bola y avisa al campo que ha terminado
    public void DestroyBall(Ball ball)
    {
        
        ++ball.myField.simulationsFinished;       
        Destroy(ball.gameObject);

    }

    //Inicia la simulación del campo principal
    public void StartSimulation()
    {
       
        mainField.originalParameters = bestValues;
        mainField.steps = steps;
        mainField.StartSimulation();

    }

    //Recorremos todos los campos en juego buscando el mejor resultado
    public void SimulationHasFinished()
    {

        if (bestValues.distance > mainField.bestParameters.distance)
            bestValues = new Parameters(mainField.bestParameters);

        if (onHill)
        {
            if (bestValues.distance < mainField.bestParameters.distance)
                bestValues = mainField.bestParameters;

            
            for (short i = 0; i < fieldsToHill.Count; ++i)
            {
                if (bestValues.distance > fieldsToHill[i].bestParameters.distance)
                {
                    bestValues = new Parameters(fieldsToHill[i].bestParameters);
                    steps = new Steps(allCurrentSteps[i]);
                    indexClimbing = 1.5f;
                    
                }
                    
            }
        }

        bestScore = bestValues.distance;

    }

    public void FinishSimulation()
    {
        ++simulationsFinished;
    }


    //Setea los steps nuevos para todos los campos
    void HillClimbing()
    {

        allCurrentSteps.Clear();

        //Algoritmo para calcular los 27 casos
        for (byte i=0; i<3; ++i)
        {
            for (byte j = 0; j < 3; ++j)
            {
                for (byte k = 0; k < 3; ++k)
                {

                    currentSteps = new Steps(steps);
                    switch (i){

                        case 0: break;
                        case 1: currentSteps.power *= indexClimbing; break;
                        case 2: currentSteps.power /= indexClimbing; break;

                    }
                    switch (j)
                    {

                        case 0: break;
                        case 1: currentSteps.angleX *= indexClimbing;  break;
                        case 2: currentSteps.angleX /= indexClimbing;  break;

                    }
                    switch (k)
                    {

                        case 0: break;
                        case 1: currentSteps.angleY *= indexClimbing;  break;
                        case 2: currentSteps.angleY /= indexClimbing;  break;

                    }

                    //Clampeamos los valores para que no sean desorbitados
                    currentSteps.angleY = Mathf.Clamp(currentSteps.angleY, 0.05f, 720.0f);
                    currentSteps.angleX = Mathf.Clamp(currentSteps.angleX, 0.05f, 720.0f);
                    currentSteps.power  = Mathf.Clamp(currentSteps.power , 0.1f , 80.0f) ;
                    //Añadimos el step a la lista
                    allCurrentSteps.Add(new Steps(currentSteps));

                }
            }
        }

      
    }

    //Recoge todos los campos principales
    public void GetFields()
    {
        
        //Mains
        for(short i=1; i<4; ++i)
            for (short j = 1; j < 10; ++j)
                fieldsToHill.Add(GameObject.Find("HillClimbing/" + i + "/" + j + "/" + "Field 0").GetComponent<Field>());
                
        
    }


    


}

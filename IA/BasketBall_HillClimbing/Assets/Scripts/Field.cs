using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Field : MonoBehaviour
{
    
    public List<Transform> neighbourPositions;  //Posiciones de los campos vecinos
    [SerializeField]
    List<Parameters> neighbourParameters;       //Parametros de los campos vecinos

    public Parameters originalParameters;       //Parametros base
    public Parameters bestParameters;           //Mejores parámetros

    public Steps steps;                         //Step que se aplica a los vecinos                        
    public bool hasFinished;                    //Ha terminado este campo
    public int simulationsFinished;             //Numero de campos finalizados

    //Inicializa el campo
    private void Awake()
    {

        neighbourPositions = new List<Transform>();
        originalParameters = new Parameters();

        //Positions
        for (short i = 0; i < gameObject.transform.parent.childCount; ++i)
            neighbourPositions.Add(gameObject.transform.parent.GetChild(i).GetChild(2).transform);

        //Parameters
        for (int i = 0; i < neighbourPositions.Count; ++i)
            neighbourParameters.Add(new Parameters());
    }
    // Start is called before the first frame update
    void Start()
    {


    }

    // Update is called once per frame
    void Update()
    {
        //Si han terminado todos los campos, comprobamos cual es el mejor resultado y avisamos al controller de que ha terminado
        if(simulationsFinished >= neighbourPositions.Count)
        {
            checkBestOne();
            GameController.instance.FinishSimulation();
            hasFinished = true;
            simulationsFinished = 0;
        }
    }

    //Iniciamos las simulaciones de los vecinos
    public void StartSimulation()
    {
        hasFinished = false;
        bestParameters = originalParameters;
        SetNeighbourParameters();

        for (int i = 0; i < neighbourPositions.Count; ++i)
        {
            //Instanciamos e inicializamos los parámetros de la bola
            neighbourParameters[i].distance = 100000;
            Ball ball = Instantiate(GameController.instance.prefab, neighbourPositions[i].position, Quaternion.identity).GetComponent<Ball>();
            ball.transform.Translate(0.0f, 0.1f, -0.2f);
            ball.Initialize();
            ball.myField = this;
            ball.parameters = neighbourParameters[i];            
            ball.started = true;
        }
        
    }

    //Setea los valores en función de los steps
    void SetNeighbourParameters()
    {
        //0 MAIN
        //1/2 Fuerza
        //3/4 X
        //5/6 Y

        for (int i = 0; i < neighbourPositions.Count; ++i)
            neighbourParameters[i] = new Parameters(originalParameters);


        //Fuerza
        if (originalParameters.power - steps.power > 0)
            neighbourParameters[1].power = originalParameters.power - steps.power;        
        neighbourParameters[2].power = originalParameters.power + steps.power;

        //AngleX        
        neighbourParameters[3].angleX = originalParameters.angleX - steps.angleX;        
        neighbourParameters[4].angleX = originalParameters.angleX + steps.angleX;

        //AngleY        
        neighbourParameters[5].angleY = originalParameters.angleY - steps.angleY;        
        neighbourParameters[6].angleY = originalParameters.angleY + steps.angleY;

    }

    //Función que avisa que se ha termianado una simulación
    void SimulationHasFinished()
    {

        ++simulationsFinished;

    }

    //Comprueba el mejor resultado entre todos los campos
    void checkBestOne()
    {
        for (byte i = 0; i < neighbourParameters.Count; ++i)
        {
            if (bestParameters.distance > neighbourParameters[i].distance)
            {
                bestParameters = neighbourParameters[i];

            }
        }

    }


}

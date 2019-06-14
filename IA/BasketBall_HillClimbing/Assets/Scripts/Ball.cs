using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour {

    // Use this for initialization

    public Parameters parameters;     //Parametros de la bola
    public Vector3 rotation;          // Vector con la rotación (depende de los parametros)
    public Vector3 windForce;         //Viento que se le aplica
    public Field myField;             //Campo al que perteneces
    float lifeTime = 5;               //Tiempo de vida
    
    bool shooted;                     //Ha sido disparado
    public  bool started;             //Se ha inicializado
    

    void Start () {
        
    }
	
	// Update is called once per frame
	void Update () {
        
        if(shooted)//Si es disparada se le aplica el viento
            this.GetComponent<Rigidbody>().AddForce(windForce, ForceMode.Force);
        
        if ( !shooted && started) //Le damos los valores que nos pasan por los paramertros y le damos el impulso de lanzamiento
        {
            parameters.distance = 1000;
            rotation.Set(parameters.angleX, parameters.angleY, 0);
            transform.eulerAngles = rotation;           
            this.GetComponent<Rigidbody>().AddForce(transform.forward* parameters.power, ForceMode.Impulse);
            shooted = true;

        }

    }

    //Funcion que inicializa la bola
    public void Initialize()
    {
        parameters = new Parameters();
        windForce = GameController.instance.windForce;       
        Invoke("Die", lifeTime);//Creamos un timer para que si no ha sido destruida por el entorno, se elimine al cabo de un tiempo

    }


    
    //Llama al controlador para destruir la bola
    public void Die()
    {
        GameController.instance.DestroyBall(this); 
        

    }
}

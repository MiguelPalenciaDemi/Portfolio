using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SensorSphere : MonoBehaviour
{
    public Transform goal;//Basket Position
    public float penalty = 0;
    public bool punisher = false;
    

    //Se activará cuando un objeto este dentro del trigger
    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.tag == "Player")//Si es una bola, comprobamos a que distancia está
            CheckDistance(other);
    }

    public void CheckDistance(Collider other)
    {
        float distance = Vector3.Distance(goal.position, other.transform.position);//Calculamos la distancia
        if (punisher)//Tiene alguna penalización o recompensa
        {
            if(penalty<0 && distance<other.GetComponent<Ball>().parameters.distance)//Si es positiva, quedate con la distancia si es mejor que la que ya tienes
             other.GetComponent<Ball>().parameters.distance = distance;
             else if(penalty > 0) //Si penaliza sobrescribe la distancia
                other.GetComponent<Ball>().parameters.distance = distance;
        }           
        else 
            other.GetComponent<Ball>().parameters.distance = distance; 



    }
}

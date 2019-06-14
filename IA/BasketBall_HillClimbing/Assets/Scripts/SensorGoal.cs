using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SensorGoal : MonoBehaviour
{
    public Transform goal;//Basket Position
    public float penalty = 2;
    
    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player")//Si sale una bola, comprobamos su distancia
          CheckDistance(other);
    }

    public void CheckDistance(Collider other)
    {
        float distance = Vector3.Distance(goal.position, other.transform.position);                   //Calculamos la distancia

        if (GetComponent<KillZone>() && distance < other.GetComponent<Ball>().parameters.distance)    //Si es una killZone y la distancia es menor a la que ya guardaba, actualizamos
            other.GetComponent<Ball>().parameters.distance = distance;      
        else 
            other.GetComponent<Ball>().parameters.distance = distance + penalty;
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KillZone : MonoBehaviour
{
    
    private void OnTriggerExit(Collider other)
    {
       
        this.gameObject.GetComponent<SensorGoal>().CheckDistance(other);             //Comprueba la distancia a la que ha llegado
        GameController.instance.DestroyBall(other.gameObject.GetComponent<Ball>());  //Destruimos la bola
                
    }
   
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Parameters
{
    public float angleX;
    public float angleY;
    public float power;
    public float distance= 100000;
    public void RandomStart()
    {
        angleX = UnityEngine.Random.Range(-60, 0);
        angleY = UnityEngine.Random.Range(-60, 60);
        power  = UnityEngine.Random.Range(5, 60);
        distance  = 100000;
    }
    public Parameters()
    {
        

    }
    public Parameters(Parameters newParameters)
    {

        angleX = newParameters.angleX;
        angleY = newParameters.angleY;
        power = newParameters.power;
        distance = newParameters.distance;
    }
}



[System.Serializable]
public class Steps
{

    public float power;
    public float angleX;
    public float angleY;

    public Steps() {

        power = 10;
        angleX = 20;
        angleY = 20;

    }

    public Steps(float power, float angleX, float angleY)
    {

        this.power = power;
        this.angleX = angleX;
        this.angleY = angleY;

    }

    public Steps(Steps steps)
    {

        power = steps.power;
        angleX = steps.angleX;
        angleY = steps.angleY;

    }
    
}





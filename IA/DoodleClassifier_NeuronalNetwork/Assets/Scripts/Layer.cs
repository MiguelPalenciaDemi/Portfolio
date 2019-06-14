using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Layer
{

    public int nodeNumber, nodeChildNumber, nodeParentNumber;
    public float[,] weights;
    public float[,] weightsIncrement;
    public float[] neuronalValues;
    public float[] desiredValues;
    public float[] errors;
    public float[] biasValues;
    public float[] biasWeights;

    public Layer parentLayer, childLayer;


    public Layer(int nNodeParents, int nNodes, int nNodeChilds)
    {
        nodeNumber = nNodes;
        nodeParentNumber = nNodeParents;
        nodeChildNumber = nNodeChilds;
        childLayer = null;
        parentLayer = null;
    }

    public void Initializer (int nNodes, Layer parent, Layer child)
    {

        nodeNumber = nNodes;
        neuronalValues = new float[nNodes];
        desiredValues = new float[nNodes];
        errors = new float[nNodes];

        //Set layers
        if(parent != null)  //Not input layer
        {
            parentLayer = parent;
            nodeParentNumber = parent.nodeNumber;
        }
        else
        {
            parentLayer = null;
            nodeParentNumber = 0;
        }

        if(child != null)   //Not output layer
        {
            childLayer = child;
            nodeChildNumber = child.nodeNumber;
            weights = new float[nodeNumber, nodeChildNumber];
            weightsIncrement = new float[nodeNumber, nodeChildNumber];

            biasValues = new float[nodeChildNumber];
            biasWeights = new float[nodeChildNumber];
        }
        else
        {
            childLayer = null;
            nodeChildNumber = 0;
            weightsIncrement = null;
            biasWeights = null;
            biasValues = null;
            weights = null;
        }
        
        //Set neural values
        for(int i = 0; i<nodeNumber; ++i)
        {
            neuronalValues[i] = 0;
            desiredValues [i] = 0;
            errors        [i] = 0;
        }

        //Set weights + bias
        if(child != null)
        {

            for (int i = 0; i < nodeNumber; ++i)
                for (int j = 0; j < nodeChildNumber; ++j)
                {
                    weights[i,j] = 0;
                    weightsIncrement[i,j] = 0;
                }
            
            for (int j = 0; j < nodeChildNumber; ++j)
            {
                biasValues[j] = -1;
                biasWeights[j] = 0;
            }

        }
    }

    public void SetWeightRandom()
    {

        if (childLayer != null)
        {

            //Normal
            for (int i = 0; i < nodeNumber; ++i)
                for (int j = 0; j < nodeChildNumber; ++j)
                    weights[i, j] = Random.Range(-1.0f,1.0f);

            //Bias
            for (int j = 0; j < nodeChildNumber; ++j)
                biasWeights[j] = Random.Range(-1.0f, 1.0f);

        }
    }

    public void CalculateNeuronalValues()
    {

        if(parentLayer != null)
            for(int j = 0; j< nodeNumber; ++j)
            {

                float x = 0;

                //Final value += value * weight + biasWeight
                for(int i = 0;i<nodeParentNumber; ++i)                
                    x += parentLayer.neuronalValues[i] * parentLayer.weights[i, j];
                x += parentLayer.biasValues[j] * parentLayer.biasWeights[j];

                //Set value
                if (childLayer == null && ConstantValues.OUTPUT_LINEAL)
                    neuronalValues[j] = x;                
                else
                    neuronalValues[j] = 1.0f / (1 + Mathf.Exp(-x));

            }

    }
    

    public void CalculateErrors()
    {

        //Output layer
        if (childLayer == null)
            for (int i = 0; i< nodeNumber; ++i)
                errors[i] = (desiredValues[i] - neuronalValues[i]) * neuronalValues[i] * (1-neuronalValues[i]);

        //Not input layer
        else if(parentLayer != null)
            for(int i = 0; i< nodeNumber; ++i)
            {
                float add = 0;

                for (int j = 0; j < nodeChildNumber; ++j)
                    add += childLayer.errors[j] * weights[i, j];

                errors[i] = add * neuronalValues[i] * (1 - neuronalValues[i]);
            }

    }

    public void SetWeights()
    {
        //Not output layer
        if(childLayer != null)
        {

            //Normal
            for(int i = 0; i< nodeNumber; ++i)
                for(int j = 0; j< nodeChildNumber; ++j)
                {
                    float dw = ConstantValues.RATIO_LEARNING * childLayer.errors[j] * neuronalValues[j];

                    if (ConstantValues.USING_INERTIA)
                    {
                        weights[i, j] += dw + ConstantValues.RATIO_INERTIA * weightsIncrement[i, j];
                        weightsIncrement[i, j] = dw;
                    }
                    else
                        weights[i, j] += dw;
                }

            //Bias
            for ( int j = 0; j < nodeChildNumber; ++j)
            {
                float dw = ConstantValues.RATIO_INERTIA * childLayer.errors[j] * biasValues[j];
                biasWeights[j] += dw;
            }

        }

    }

}
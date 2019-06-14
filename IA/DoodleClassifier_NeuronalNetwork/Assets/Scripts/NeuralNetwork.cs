using UnityEngine;

public class NeuralNetwork
{

    //Layers
    private Layer inputLayer, hiddenLayer, outputLayer;

    public NeuralNetwork(int nInputNodes, int nHiddenNodes, int nOutputNodes)
    {

        inputLayer = new Layer(0, nInputNodes, nHiddenNodes);
        hiddenLayer = new Layer(nInputNodes, nHiddenNodes, nOutputNodes);
        outputLayer = new Layer(nHiddenNodes, nOutputNodes, 0);

        //Initialize
        inputLayer.Initializer(nInputNodes, null, hiddenLayer);
        hiddenLayer.Initializer(nHiddenNodes, inputLayer, outputLayer);
        outputLayer.Initializer(nOutputNodes, hiddenLayer, null);

        //Set initial weights
        inputLayer.SetWeightRandom();
        hiddenLayer.SetWeightRandom();
        
    }

    public void SetInput(int i, float value)
    {
        if (i >= 0 && i < inputLayer.nodeNumber)
            inputLayer.neuronalValues[i] = value;
    }

    public float GetOutput(int i)
    {
        if (i >= 0 && i < outputLayer.nodeNumber)
            return outputLayer.neuronalValues[i];
        else
            return -1;
    }

    public void SetDesiredOutput (int i, float value)
    {
        if (i >= 0 && i < outputLayer.nodeNumber)
            outputLayer.desiredValues[i] = value;
    }

    //Calculate neural values
    public void FeedForward()
    {
        inputLayer.CalculateNeuronalValues();
        hiddenLayer.CalculateNeuronalValues();
        outputLayer.CalculateNeuronalValues();
    }

    public void BackPropagation()
    {
        //Calculate error
        outputLayer.CalculateErrors();
        hiddenLayer.CalculateErrors();

        //Correct weights
        hiddenLayer.SetWeights();
        inputLayer.SetWeights();
    }

    //Get maximum output (result)
    public int GetMaxOutputId()
    {

        int id = -1;
        float max = float.MinValue;
        
        for(int i = 0; i< outputLayer.nodeNumber; ++i)
        {

            Debug.Log("VALOR OUTPUT en " + i + ": " + outputLayer.neuronalValues[i]);

            if (outputLayer.neuronalValues[i] > max)
            {
                max = outputLayer.neuronalValues[i];
                id = i;
            }

        }

        return id;

    }

    public float CalculateError()
    {

        float error = 0;

        for (int i = 0; i < outputLayer.nodeNumber; ++i)
            error += Mathf.Pow( outputLayer.neuronalValues[i] - outputLayer.desiredValues[i], 2);

        error /= outputLayer.nodeNumber;

        return error;

    }

    //Getters
    public Layer GetInputLayer()
    {
        return inputLayer;
    }

    public Layer GetHiddenLayer()
    {
        return hiddenLayer;
    }
    
}
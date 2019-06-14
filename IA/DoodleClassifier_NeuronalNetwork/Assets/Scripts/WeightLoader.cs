using System;
using UnityEngine;

public class WeightLoader : MonoBehaviour
{

    [SerializeField]
    string fileNameWeights;


    public void SaveWeights()
    {
        
        //Input weights
        float[,] weights = GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetInputLayer().weights;
        float[] weightsInput = ToUnidimentional(weights);                                                               //From bidimentional to unidimentional

        for (int i = 5; i >= 0; --i)
            Debug.Log(weightsInput[weightsInput.Length-i-1]);
        Debug.Log(weightsInput.Length);

        byte[] byteArrayInput = new byte[weightsInput.Length * 4];
        Buffer.BlockCopy(weightsInput, 0, byteArrayInput, 0, byteArrayInput.Length);                                    //float[] to byte[]

        SaveManager.Instance.Save(
            byteArrayInput, "Assets\\SavingData\\" + fileNameWeights + "Input.bin", OnSaveSuccess, OnSaveError);        //Save


        //Input weights
        float[,] weights2 = GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetHiddenLayer().weights;
        float[] weightsHidden = ToUnidimentional(weights2);

        byte[] byteArrayHidden = new byte[weightsHidden.Length * 4];
        Buffer.BlockCopy(weightsHidden, 0, byteArrayHidden, 0, byteArrayHidden.Length);

        SaveManager.Instance.Save(
            byteArrayHidden, "Assets\\SavingData\\" + fileNameWeights + "Hidden.bin", OnSaveSuccess, OnSaveError);


        //Bias input weights
        float[] weightsBiasInput = GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetInputLayer().biasWeights;

        byte[] byteArrayBiasInput = new byte[weightsBiasInput.Length * 4];
        Buffer.BlockCopy(weightsBiasInput, 0, byteArrayBiasInput, 0, byteArrayBiasInput.Length);

        SaveManager.Instance.Save(
            byteArrayBiasInput, "Assets\\SavingData\\" + fileNameWeights + "BiasInput.bin", OnSaveSuccess, OnSaveError);


        //Bias hidden weights
        float[] weightsBiasHidden = GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetHiddenLayer().biasWeights;

        byte[] byteArrayBiasHidden = new byte[weightsBiasHidden.Length * 4];
        Buffer.BlockCopy(weightsBiasHidden, 0, byteArrayBiasHidden, 0, byteArrayBiasHidden.Length);

        SaveManager.Instance.Save(
            byteArrayBiasHidden, "Assets\\SavingData\\" + fileNameWeights + "BiasHidden.bin", OnSaveSuccess, OnSaveError);


        //Error and epoch
        float[] errorEpoch = GetComponent<NeuralNetworkImage>().GetErrorEpoch();

        byte[] byteArrayErrorEpoch = new byte[errorEpoch.Length * 4];
        Buffer.BlockCopy(errorEpoch, 0, byteArrayErrorEpoch, 0, byteArrayErrorEpoch.Length);

        SaveManager.Instance.Save(
            byteArrayErrorEpoch, "Assets\\SavingData\\" + fileNameWeights + "ErrorEpoch.bin", OnSaveSuccess, OnSaveError);

    }

    public void LoadWeights()
    {
        SaveManager.Instance.Load("Assets\\SavingData\\" + fileNameWeights + "Input.bin", OnLoadSuccessInput, OnLoadError);
        SaveManager.Instance.Load("Assets\\SavingData\\" + fileNameWeights + "Hidden.bin", OnLoadSuccessHidden, OnLoadError1);
        SaveManager.Instance.Load("Assets\\SavingData\\" + fileNameWeights + "BiasInput.bin", OnLoadSuccessBiasInput, OnLoadError2);
        SaveManager.Instance.Load("Assets\\SavingData\\" + fileNameWeights + "BiasHidden.bin", OnLoadSuccessBiasHidden, OnLoadError3);
        SaveManager.Instance.Load("Assets\\SavingData\\" + fileNameWeights + "ErrorEpoch.bin", OnLoadSuccessErrorEpoch, OnLoadError4);
    }


    void OnSaveSuccess()
    {
        Debug.Log("Save successful");
    }
    void OnSaveError()
    {
        Debug.Log("Save error");
    }

    void OnLoadError()
    {
        Debug.Log("Load error input");
    }
    void OnLoadError1()
    {
        Debug.Log("Load error hidden");
    }
    void OnLoadError2()
    {
        Debug.Log("Load error biasInput");
    }
    void OnLoadError3()
    {
        Debug.Log("Load error biasHidden");
    }
    void OnLoadError4()
    {
        Debug.Log("Load Error epoch/error");
    }


    void OnLoadSuccessInput(byte[] data)
    {
        
        Debug.Log("Load input successful");
        
        float[] weightsInput = new float[data.Length / 4];
        Buffer.BlockCopy(data, 0, weightsInput, 0, data.Length);                                                        //byte[] to float[]

        float[,] result = ToBidimentional(  weightsInput,                                                               //From unidimentional to bidimentional
                                            GetComponent<NeuralNetworkImage>().numInput,
                                            GetComponent<NeuralNetworkImage>().numHidden);

        for (int i = 5; i >= 0; --i)                                                                                    //Debug last 5
            Debug.Log(result[result.GetLength(0)-1, result.GetLength(1) - i - 1]);

        for (int i = 0; i < result.GetLength(0); ++i)
            for (int j = 0; j < result.GetLength(1); ++j)
                GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetInputLayer().weights[i, j] = result[i, j];     //Copy values into neural network

    }

    void OnLoadSuccessHidden(byte[] data)
    {

        Debug.Log("Load hidden successful");

        float[] weightsHidden = new float[data.Length / 4];
        Buffer.BlockCopy(data, 0, weightsHidden, 0, data.Length);

        float[,] result = ToBidimentional(  weightsHidden,
                                            GetComponent<NeuralNetworkImage>().numHidden,
                                            GetComponent<NeuralNetworkImage>().numOutput);
        
        for (int i = 0; i < result.GetLength(0); ++i)
            for (int j = 0; j < result.GetLength(1); ++j)
                GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetHiddenLayer().weights[i, j] = result[i, j];

    }

    void OnLoadSuccessBiasInput(byte[] data)
    {

        Debug.Log("Load bias input successful");

        float[] weightBias = new float[data.Length / 4];
        Buffer.BlockCopy(data, 0, weightBias, 0, data.Length);

        for (int i = 0; i < weightBias.Length; ++i)
            GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetInputLayer().biasWeights[i] = weightBias[i];

    }

    void OnLoadSuccessBiasHidden(byte[] data)
    {

        Debug.Log("Load bias hidden successful");

        float[] weightBias = new float[data.Length / 4];
        Buffer.BlockCopy(data, 0, weightBias, 0, data.Length);

        for (int i = 0; i < weightBias.Length; ++i)
            GetComponent<NeuralNetworkImage>().GetNeuralNetwork().GetHiddenLayer().biasWeights[i] = weightBias[i];

    }

    void OnLoadSuccessErrorEpoch(byte[] data)
    {

        Debug.Log("Load error and epoch successful");

        float[] errorEpoch = new float[data.Length / 4];
        Buffer.BlockCopy(data, 0, errorEpoch, 0, data.Length);

        GetComponent<NeuralNetworkImage>().SetErrorEpoch(errorEpoch[0], (int)errorEpoch[1]);

    }
    

    float[] ToUnidimentional(float[,] array)
    {

        float[] result = new float[array.GetLength(0) * array.GetLength(1)];

        for (int i = 0; i < array.GetLength(0); ++i)
            for (int j = 0; j < array.GetLength(1); ++j)
                result[i * array.GetLength(1) + j] = array[i, j];
        
        return result;

    }

    float[,] ToBidimentional(float[] array, int rows, int cols)
    {

        float[,] result = new float[rows, cols];

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result[i, j] = array[i * cols + j];

        return result;

    }


    float[,] CopyArrayBi(float[,] toCopy)
    {
        float[,] result = new float[toCopy.GetLength(0), toCopy.GetLength(1)];
        for (int i = 0; i < toCopy.GetLength(0); ++i)
            for (int j = 0; j < toCopy.GetLength(1); ++j)
                result[i, j] = toCopy[i,j];

        return result;
    }
    
}
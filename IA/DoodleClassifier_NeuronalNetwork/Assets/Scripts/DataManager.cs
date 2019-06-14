using UnityEngine;
using UnityEngine.Windows;

public class DataManager : MonoBehaviour
{

    public static DataManager instance;
    
    public Data shorts;
    public Data basket;
    public Data triangle;
    
    float[,] trainingAssets;
    float[,] testAssets;
    

    // Start is called before the first frame update
    void Start()
    {

        instance = this;
        
        byte[] source;
        source = File.ReadAllBytes("Assets/Data/shorts20000.bin");        
        shorts = new Data(source, 1);
        source = File.ReadAllBytes("Assets/Data/basketball20000.bin");
        basket = new Data(source, 2);
        source = File.ReadAllBytes("Assets/Data/triangle20000.bin");
        triangle = new Data(source, 3);

        //Train data
        trainingAssets = new float[3 * 16000, ConstantValues.TOTAL_SIZE_TRAINING];
        trainingAssets = UnifyTrainData();
        
        ShuffleAllTrainData();
        
        //Test data
        testAssets = new float[3 * 4000, ConstantValues.TOTAL_PIXELS];
        testAssets = UnifyTestData();
        
    }


    public void ShuffleAllTrainData()
    {

        int iterations = 500000;
        int totalTrainImages = trainingAssets.GetLength(0);

        for (int i = 0; i < iterations; ++i)
        {

            int rand1 = Random.Range(0, totalTrainImages-1);
            int rand2 = Random.Range(0, totalTrainImages-1);

            float aux = 0;
            for (int index = 0; index < ConstantValues.TOTAL_SIZE_TRAINING; ++index)
            {
                aux = trainingAssets[rand1, index];
                trainingAssets[rand1, index] = trainingAssets[rand2, index];
                trainingAssets[rand2, index] = aux;
            }
            
        }
        
    }

    float[,] UnifyTrainData()
    {
        
        float[,] allData = new float[   shorts.training.data.GetLength(0) +
                                        basket.training.data.GetLength(0) +
                                        triangle.training.data.GetLength(0), 
                                        ConstantValues.TOTAL_SIZE_TRAINING];

        //Unify data

        //Shorts
        for (int i=0; i< shorts.training.data.GetLength(0); ++i)
            for (int j = 0; j < ConstantValues.TOTAL_SIZE_TRAINING; ++j)
                allData[i, j] = shorts.training.data[i, j];

        //Basket
        for (int i = shorts.training.data.GetLength(0), k=0; k < basket.training.data.GetLength(0); ++i, ++k)
            for (int j = 0; j < ConstantValues.TOTAL_SIZE_TRAINING; ++j)
                allData[i, j] = basket.training.data[k, j];

        //Triangle
        for (int i = shorts.training.data.GetLength(0) + basket.training.data.GetLength(0), k=0; k < triangle.training.data.GetLength(0); ++i, ++k)
            for (int j = 0; j < ConstantValues.TOTAL_SIZE_TRAINING; ++j)
                allData[i, j] = triangle.training.data[k, j];
        
        return allData;

    }

    float[,] UnifyTestData()
    {

        float[,] allData = new float[   shorts.testing.GetLength(0) +
                                        basket.testing.GetLength(0) +
                                        triangle.testing.GetLength(0),
                                        ConstantValues.TOTAL_PIXELS];

        //Unify data

        //Shorts
        for (int i = 0; i < shorts.testing.GetLength(0); ++i)
            for (int j = 0; j < ConstantValues.TOTAL_PIXELS; ++j)
                allData[i, j] = shorts.testing[i, j];

        //Basket
        for (int i = shorts.testing.GetLength(0), k = 0; k < basket.testing.GetLength(0); ++i, ++k)
            for (int j = 0; j < ConstantValues.TOTAL_PIXELS; ++j)
                allData[i, j] = basket.testing[k, j];

        //Triangle
        for (int i = shorts.testing.GetLength(0) + basket.testing.GetLength(0), k = 0; k < triangle.testing.GetLength(0); ++i, ++k)
            for (int j = 0; j < ConstantValues.TOTAL_PIXELS; ++j)
                allData[i, j] = triangle.testing[k, j];

        return allData;

    }

    //Getters
    public float[,] GetTrainingData()
    {
        return trainingAssets;
    }

    public float[,] GetTestingData()
    {
        return testAssets;
    }
    
}
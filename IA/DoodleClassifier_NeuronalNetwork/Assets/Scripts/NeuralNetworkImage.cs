using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class NeuralNetworkImage : MonoBehaviour
{

    public static NeuralNetworkImage instance;

    private NeuralNetwork net;
    public int numInput = ConstantValues.TOTAL_PIXELS, numHidden = 30, numOutput = 3;
    
    [SerializeField]
    Text resultText;
    [SerializeField]
    Text errorText;
    [SerializeField]
    Text epochText;

    float[] errorEpoch;
    int totalEpoch;     //Each row in train

    //Index of the image selected in test data
    int imageSelected;



    // Start is called before the first frame update
    void Start()
    {

        instance = this;

        net = new NeuralNetwork(numInput, numHidden, numOutput);

        errorEpoch = new float[2];
        totalEpoch = 0;

    }


    //Initial train
    public void StartTraining()
    {
        StartCoroutine("TrainNet");
    }


    IEnumerator TrainNet()
    {

        float error = 1;
        
        while ((error > 0.05f) && (totalEpoch < ConstantValues.TOTAL_EPOCH))
        {

            error = 0;
            totalEpoch++;

            DataManager.instance.ShuffleAllTrainData();
            for (int i = 0; i < DataManager.instance.GetTrainingData().GetLength(0); ++i)
            {
                
                //Set input data
                for (int j = 0; j < numInput; ++j)
                    net.SetInput(j, DataManager.instance.GetTrainingData()[i, j]);
                
                //Set desired output data
                switch(DataManager.instance.GetTrainingData()[i, ConstantValues.TOTAL_SIZE_TRAINING - 1])
                {
                    case 1:
                        net.SetDesiredOutput(0, 0.9f);
                        net.SetDesiredOutput(1, 0.1f);
                        net.SetDesiredOutput(2, 0.1f);
                        break;

                    case 2:
                        net.SetDesiredOutput(0, 0.1f);
                        net.SetDesiredOutput(1, 0.9f);
                        net.SetDesiredOutput(2, 0.1f);
                        break;

                    case 3:
                        net.SetDesiredOutput(0, 0.1f);
                        net.SetDesiredOutput(1, 0.1f);
                        net.SetDesiredOutput(2, 0.9f);
                        break;
                }

                //Feed forward, calculate error and correct weights(back propagation)
                net.FeedForward();
                error += net.CalculateError();
                net.BackPropagation();

            }

            error /= DataManager.instance.GetTrainingData().GetLength(0);

        }

        Debug.Log("ENTRENAMIENTO TERMINADO");
        //Save error and epoch to be able to save them in external data
        SetErrorEpoch(error, totalEpoch);

        yield return null;

    }

    
    //Ask for a result
    public void Guess()
    {

        ////With a drawed image
        //float[] image = new float[ConstantValues.TOTAL_PIXELS];
        //Color[] pixels = GetComponent<Image>().sprite.texture.GetPixels();      //Pixels RGBA

        //for (int i = 0; i < image.Length; ++i)                                  //Pixels grayscale
        //    image[i] = pixels[i].grayscale;

        //QueryAction(image);
        
        //With a saved/loaded image
        float[] image = new float[ConstantValues.TOTAL_PIXELS];
        for (int i = 0; i < image.Length; ++i)
            image[i] = DataManager.instance.GetTestingData()[imageSelected, i];
        
        QueryAction(image);
        
    }
    
    //Result of guessing
    void QueryAction(float[] input)
    {

        for (int j = 0; j < numInput; ++j)
            net.SetInput(j, input[j]);

        net.FeedForward();

        switch ((byte)net.GetMaxOutputId())
        {
            case 0:
                resultText.text = "Short";
                break;

            case 1:
                resultText.text = "Basket";
                break;

            case 2:
                resultText.text = "Triangle";
                break;
        }
        
    }


    public void ChargeNewImage()
    {

        int totalTestImages = DataManager.instance.GetTestingData().GetLength(0);
        int randomIndex = Random.Range(0, totalTestImages-1);
        imageSelected = randomIndex;                                                    //For saved/loaded image option
        Texture2D t = new Texture2D(28, 28);
        
        //Set pixels
        for (int i = 0; i < t.width; ++i)
            for (int j = 0; j < t.height; ++j)
            {
                float gray = DataManager.instance.GetTestingData()[randomIndex, i*t.width + j];
                t.SetPixel(j, i, new Color(gray, gray, gray));
            }

        //Set sprite
        GetComponent<Image>().sprite = Sprite.Create(t, new Rect(0.0f, 0.0f, t.width, t.height), Vector2.zero);

        //Apply
        t.Apply();
        
    }
    

    public NeuralNetwork GetNeuralNetwork()
    {
        return net;
    }

    public float[] GetErrorEpoch()
    {
        return errorEpoch;
    }

    public void SetErrorEpoch(float error, int epoch)
    {

        errorText.text = "" + error;
        epochText.text = "" + epoch;
        errorEpoch[0] = error;
        errorEpoch[1] = epoch;
        totalEpoch = epoch;

    }
    
}
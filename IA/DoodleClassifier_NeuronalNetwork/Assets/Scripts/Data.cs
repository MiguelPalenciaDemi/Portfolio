using UnityEngine;


public struct TrainingData
{

    public byte label;
    public float[,] data;

    public TrainingData(byte label=0)
    {
        data = new float[16000, ConstantValues.TOTAL_SIZE_TRAINING];    //16000 per type
        this.label = label;
    }
    
}


public class Data
{

    int len;    //Total images per type
    int total;  //Total pixels per image

    public TrainingData training;
    public float[,] testing;
    
    
    public Data(byte[] data, byte label)
    {

        total = ConstantValues.TOTAL_IMAGES;
        len = ConstantValues.TOTAL_PIXELS;
        testing = new float[(int)Mathf.Floor(0.2f * total), len];       //4000 (images for testing)
        training = new TrainingData(label);                             //4000 (images for testing)

        for(int i = 0; i < total; i++)
        {

            int offset = i*len;
            int threshold = (int)Mathf.Floor(0.8f*total);               //16000 (images for training)

            //Training
            if (i < threshold)                                          
            { 
                for(int p = 0; p < len; ++p)
                    training.data[i, p] = data[offset+p]/255.0f;

                training.label = label;
                training.data[i, ConstantValues.TOTAL_PIXELS] = label;
            }
            //Testing
            else
                for (int p = 0; p < len; ++p)
                    testing[i - threshold, p] = data[offset + p]/255.0f;
            
        }
        
    }
    
}
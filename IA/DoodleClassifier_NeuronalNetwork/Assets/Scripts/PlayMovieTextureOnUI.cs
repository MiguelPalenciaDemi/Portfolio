using UnityEngine;
using UnityEngine.UI;

public class PlayMovieTextureOnUI : MonoBehaviour
{

    [SerializeField]
    bool realTime;                  //Replica in real time?
    [SerializeField]
    bool grayScale;                 //Some grayscale? (At run time is very slow)

    //Original
    public RawImage rawImage;       

    //Replica
    public Image im;                
    //Replica's texture
    Texture2D t;                    

    //Camera image
    WebCamTexture webcamTexture;    


    void Start()
    {

        webcamTexture = new WebCamTexture();
        rawImage.texture = webcamTexture;
        webcamTexture.Play();
        
        t = new Texture2D(webcamTexture.width, webcamTexture.height);
        im.sprite = Sprite.Create(t, new Rect(0.0f, 0.0f, t.width, t.height), Vector2.zero);
        t.Apply();

    }
    

    private void Update()
    {
        
        if (Input.anyKeyDown)
        {
            
            //ScreenShot
            if (!realTime)
                CopyCamera();
            
        }

        //Real time
        if (realTime)
            CopyCamera();
        
    }


    void CopyCamera()
    {

        //Set pixels
        if (grayScale)
            for (int i = 0; i < t.width; ++i)
            {
                for (int j = 0; j < t.height; ++j)
                {
                    float gray = webcamTexture.GetPixel(i, j).grayscale;
                    t.SetPixel(i, j, new Color(gray, gray, gray));
                }
            }
        else
            t.SetPixels(webcamTexture.GetPixels());
        
        //Set sprite
        im.sprite = Sprite.Create(t, new Rect(0.0f, 0.0f, t.width, t.height), Vector2.zero);

        //Apply
        t.Apply();

    }
    
}
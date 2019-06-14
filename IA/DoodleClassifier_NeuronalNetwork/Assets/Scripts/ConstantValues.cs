
public class ConstantValues
{

    public const bool OUTPUT_LINEAL = false;
    public const bool USING_INERTIA = true;
    public const float RATIO_LEARNING = 0.25f;          //Recommended value around 0.25
    public const float RATIO_INERTIA = 0.3f;            //Recommended value around 0.25

    public const int TOTAL_PIXELS = 784;                //Total pixels (per image)
    public const int TOTAL_IMAGES = 20000;              //Total images (per type/category)

    public const int TOTAL_SIZE_TRAINING = 784 + 1;     //Total pixels + label

    public const int TOTAL_EPOCH = 3;

}
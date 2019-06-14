using UnityEngine;
using UnityEditor;

public class DungeonGeneratorWindow : EditorWindow
{
    public GameObject floorPrefab;
    public GameObject wallPrefab;
    public GameObject dungeonPrefab;

    GameObject parentPrefab;
    string nameDungeon = "Dungeon";

    ProcGen dungeonGenerator = new ProcGen();
    
    
    int width = 20;    
    int height = 20;

    int roomMinSize = 2;
    int roomMaxSize = 3;

    int minNumRoom = 2;
    int maxNumRoom = 3;

    
    int maxMeasureRoom = 20;
    int maxNumRoomsPossible = 3;

    string dungeon = "Dungeon Preview HERE";
   

    Vector2 scrollBarDisplay;
    Vector2 scrollBar;

    bool canGenerate = false;
    bool canSave = false;

    [MenuItem("Window/Dungeon Generator")]
    public static void DisplayWindow()
    {
        GetWindow<DungeonGeneratorWindow>("Dungeon Generator");
    }

    private void OnGUI()
    {
        this.minSize = new Vector2(500,500);
        scrollBar = EditorGUILayout.BeginScrollView(scrollBar);

        GUILayout.Label("Dungeon Generator", EditorStyles.boldLabel);

        

        EditorGUI.BeginChangeCheck();       

        GUILayout.Label("Measure", EditorStyles.miniBoldLabel);       
        width = EditorGUILayout.IntSlider("Width", width,10,100);
        height = EditorGUILayout.IntSlider("Height", height, 10,100);

         GUILayout.Label("Room Size", EditorStyles.miniBoldLabel);
        roomMinSize = EditorGUILayout.IntSlider("Min", roomMinSize, 1, roomMaxSize - 1);
        roomMaxSize = EditorGUILayout.IntSlider("Max", roomMaxSize, 2, maxMeasureRoom);


        GUILayout.Label("Number of Rooms", EditorStyles.miniBoldLabel);
        minNumRoom = EditorGUILayout.IntSlider("Min", minNumRoom, 0, maxNumRoom - 1);
        maxNumRoom = EditorGUILayout.IntSlider("Max", maxNumRoom, 1, maxNumRoomsPossible);

        if (EditorGUI.EndChangeCheck())
        {          
            maxNumRoomsPossible = GetMaxNumRoomsPosible();
            maxMeasureRoom = GetMinMeasureRoom();
        }

        if (GUILayout.Button("Preview"))
        {
            dungeonGenerator.SetHeight(height);
            dungeonGenerator.SetWidth(width);
            dungeonGenerator.SetMinRoom(minNumRoom);
            dungeonGenerator.SetMaxRoom(maxNumRoom);
            dungeonGenerator.SetRoomMaxSize(roomMaxSize);
            dungeonGenerator.SetRoomMinSize(roomMinSize);

            dungeon = DrawDungeon();

            canGenerate = true;
        }

       


        scrollBarDisplay = EditorGUILayout.BeginScrollView(scrollBarDisplay);
        GUI.enabled = false;
        dungeon = EditorGUILayout.TextArea(dungeon);

        EditorGUILayout.EndScrollView();
       
        GUI.enabled = canGenerate;
        if (GUILayout.Button("Generate"))
        {
            CreateDungeon();
            canSave = true;

        }
        GUI.enabled = true;

        nameDungeon = GUILayout.TextField(nameDungeon, EditorStyles.textField);

        GUI.enabled = canSave;
        if (GUILayout.Button("Save"))
        {
            Save();
        }
        EditorGUILayout.EndScrollView();
    }

    string DrawDungeon()
    {

        dungeonGenerator.Generate();
        byte[] dungeon = dungeonGenerator.GetDungeon();
        string result = "";

        int width = dungeonGenerator.GetWidth();
        int height = dungeonGenerator.GetHeight();
               
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (dungeon[y * dungeonGenerator.GetWidth() + x] == 'X')
                {                
                    result += 'x';
                }
                    //result += 'x';
                if (dungeon[y * dungeonGenerator.GetWidth() + x] == ' ')
                {
                    result += '_';                   
                }
                
               

            }            
            result += "\n";
           

        }

       

        return result;
    }

    int GetMinMeasureRoom()
    {
        return width <= height ? width : height; 
    }

    int GetMaxNumRoomsPosible()
    {
       
        return (height * width) / (roomMaxSize * roomMaxSize);
    }

    void CreateDungeon()
    {
        
        byte[] dungeonGen = dungeonGenerator.GetDungeon();
        parentPrefab =  Instantiate(dungeonPrefab, new Vector3(0, 0, 0), Quaternion.identity);


        int width = dungeonGenerator.GetWidth();
        int height = dungeonGenerator.GetHeight();

        

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {

                //I KNOW IT COULD HAVE LESS IF CONDITIONS BUT IT'S MORE VISUAL THIS WAY... I NEEDED IT
                if (dungeonGen[y * dungeonGenerator.GetWidth() + x] == 'X')
                {

                    //First row y = 0 & x = 0
                    if(y == 0)
                    {
                        
                        if(x == 0 && (dungeonGen[y * dungeonGenerator.GetWidth() + x+1] == ' ' || dungeonGen[(y+1) * dungeonGenerator.GetWidth() + x ] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }
                        
                        else if (x == width - 1 && (dungeonGen[y * dungeonGenerator.GetWidth() + x - 1] == ' ' || dungeonGen[(y + 1) * dungeonGenerator.GetWidth() + x] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }

                        else if ((x != width - 1 && x != 0)
                             && (dungeonGen[y * dungeonGenerator.GetWidth() + x - 1] == ' ' || dungeonGen[(y + 1) * dungeonGenerator.GetWidth() + x] == ' '
                               || dungeonGen[y * dungeonGenerator.GetWidth() + x + 1] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }
                    }

                    //Last Row
                    else if (y == height-1)
                    {

                        if (x == 0 && (dungeonGen[y * dungeonGenerator.GetWidth() + x + 1] == ' ' || dungeonGen[(y - 1) * dungeonGenerator.GetWidth() + x] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }

                        else if (x == width - 1 && (dungeonGen[y * dungeonGenerator.GetWidth() + x - 1] == ' ' || dungeonGen[(y - 1) * dungeonGenerator.GetWidth() + x] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }

                        else if ((x != width - 1 && x != 0)
                             && (dungeonGen[y * dungeonGenerator.GetWidth() + x - 1] == ' ' || dungeonGen[(y - 1) * dungeonGenerator.GetWidth() + x] == ' '
                               || dungeonGen[y * dungeonGenerator.GetWidth() + x + 1] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }
                    }

                    else//Center
                    {
                        //Left Side
                        if(x == 0
                           && ( dungeonGen[(y - 1) * dungeonGenerator.GetWidth() + x] == ' '
                             || dungeonGen[y * dungeonGenerator.GetWidth() + x + 1] == ' ' || dungeonGen[(y + 1) * dungeonGenerator.GetWidth() + x] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }
                        //Right Side
                        else if (x == width - 1
                           && (dungeonGen[(y - 1) * dungeonGenerator.GetWidth() + x] == ' '
                             || dungeonGen[y * dungeonGenerator.GetWidth() + x - 1] == ' ' || dungeonGen[(y + 1) * dungeonGenerator.GetWidth() + x] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }

                        //Center
                        else if ((x != width - 1 && x != 0)
                              && (dungeonGen[y * dungeonGenerator.GetWidth() + x - 1] == ' ' || dungeonGen[(y - 1) * dungeonGenerator.GetWidth() + x] == ' '
                                || dungeonGen[y * dungeonGenerator.GetWidth() + x + 1] == ' ' || dungeonGen[(y + 1) * dungeonGenerator.GetWidth() + x] == ' '))
                        {
                            Instantiate(wallPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);
                        }


                    }

                }
                else
                    Instantiate(floorPrefab, new Vector3(x, 0, y), Quaternion.identity, parentPrefab.transform);




            }

        }

        //Select the prefab
        Selection.activeObject = parentPrefab;
        

    }

    //Save last dungeon created
    void Save()
    {        
        PrefabUtility.SaveAsPrefabAsset(parentPrefab, "Assets/Prefabs/"+nameDungeon+".prefab");
    }
}

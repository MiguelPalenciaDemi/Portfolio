using System;
using System.Collections;
using UnityEngine;
using System.IO;

public abstract class SaveManagerBase : MonoBehaviour
{

    public static SaveManagerBase Instance { get; private set; }
    bool operating = false;

    protected abstract void DoSave(byte[] data, string path,
        Action onSaveSuccess, Action onSaveError);
    protected abstract void DoLoad(string path,
        Action<byte[]> onLoadSuccess, Action onLoadError);

    public void Save(byte[] data, string path,
        Action onSaveSuccess, Action onSaveError)
    {
        StartCoroutine(SaveCoroutine(data, path, onSaveSuccess, onSaveError));
    }

    public void Load(string path,
        Action<byte[]> onLoadSuccess, Action onLoadError)
    {
        StartCoroutine(LoadCoroutine(path, onLoadSuccess, onLoadError));
    }

    IEnumerator SaveCoroutine(byte[] data, string path,
        Action onSaveSuccess, Action onSaveError)
    {
        while (operating) yield return null;
        operating = true;
        Action onSaveSuccess2 = () =>
        {
            operating = false;
            if (onSaveSuccess != null) onSaveSuccess();
        };
        Action onSaveError2 = () =>
        {
            operating = false;
            if (onSaveError != null) onSaveError();
        };
        DoSave(data, path, onSaveSuccess2, onSaveError2);
    }

    IEnumerator LoadCoroutine(string path,
        Action<byte[]> onLoadSuccess, Action onLoadError)
    {
        while (operating) yield return null;
        operating = true;
        Action<byte[]> onLoadSuccess2 = (byte[] data) =>
        {
            operating = false;
            if (onLoadSuccess != null) onLoadSuccess(data);
        };
        Action onLoadError2 = () =>
        {
            operating = false;
            if (onLoadError != null) onLoadError();
        };
        DoLoad(path, onLoadSuccess2, onLoadError2);
    }

    void Awake()
    {
        Instance = this;
        DontDestroyOnLoad(this.gameObject);
    }
}

public partial class SaveManager : SaveManagerBase
{

    protected override void DoLoad(string path, Action<byte[]> onLoadSuccess, Action onLoadError)
    {
        try
        {
            byte[] data = File.ReadAllBytes(path);
            onLoadSuccess(data);
        }
        catch
        {
            onLoadError();
        }
    }

    protected override void DoSave(byte[] data, string path, Action onSaveSuccess, Action onSaveError)
    {
        try
        {
            File.WriteAllBytes(path, data);
            onSaveSuccess();
        }
        catch
        {
            onSaveError();
        }
    }

}
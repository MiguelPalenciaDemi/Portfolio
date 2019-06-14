using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

// WRAPPER
public unsafe class ProcGen
{
    #region Native
    struct NativeProcGen { }

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern NativeProcGen* create_ProcGen();

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void destroy_ProcGen(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void generate_dungeon(NativeProcGen* ptr);    

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void set_width(NativeProcGen* ptr,int value);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void set_height(NativeProcGen* ptr, int value);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void set_room_min_size(NativeProcGen* ptr, int value);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void set_room_max_size(NativeProcGen* ptr, int value);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void set_min_rooms(NativeProcGen* ptr, int value);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern void set_max_rooms(NativeProcGen* ptr, int value);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern int get_width(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern int get_height(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern int get_room_min_size(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern int get_room_max_size(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern int get_min_rooms(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern int get_max_rooms(NativeProcGen* ptr);

    [DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    private static extern char* get_dungeon(NativeProcGen* ptr);


    //[DllImport("Dll1", CallingConvention = CallingConvention.Cdecl)]
    //private static extern string get_dungeon(NativeProcGen* ptr);



    #endregion

    NativeProcGen* nativePointer;

    #region API friendly
    public ProcGen()
    {
        nativePointer = create_ProcGen();
        generate_dungeon(nativePointer);
    }

    ~ProcGen()
    {
        destroy_ProcGen(nativePointer);
    }
    public void Generate()
    {
        generate_dungeon(nativePointer);
    }

    public void SetWidth(int value)
    {
        set_width(nativePointer, value);
    }

    public void SetHeight(int value)
    {
        set_height(nativePointer, value);
    }

    public void SetRoomMinSize(int value)
    {
        set_room_min_size(nativePointer, value);
    }

    public void SetRoomMaxSize(int value)
    {
        set_room_max_size(nativePointer, value);
    }

    public void SetMaxRoom(int value)
    {
        set_max_rooms(nativePointer, value);
    }

    public void SetMinRoom(int value)
    {
        set_min_rooms(nativePointer, value);
    }



    public int GetWidth()
    {
       return get_width(nativePointer);
    }

    public int GetHeight()
    {
        return get_height(nativePointer);
    }

    public int GetRoomMinSize()
    {
        return get_room_min_size(nativePointer);
    }

    public int GetRoomMaxSize()
    {
        return get_room_max_size(nativePointer);
    }

    public int GetMaxRoom()
    {
        return get_max_rooms(nativePointer);
    }

    public int GetMinRoom()
    {
        return get_min_rooms(nativePointer);
    }

    public byte[] GetDungeon()
    {
        IntPtr dungeon = new IntPtr(get_dungeon(nativePointer));      
        int length = GetWidth() * GetHeight();

        byte[] result = new byte[length];
        Marshal.Copy(dungeon, result, 0, length);
        
        return result;
        
    }



    #endregion
}

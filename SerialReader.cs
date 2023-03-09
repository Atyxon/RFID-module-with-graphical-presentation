using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class SerialReader : MonoBehaviour
{
    SerialPort dataStream = new SerialPort("COM3", 9600);   // Set serial port to COM3, and boudrate to 9600
    public string receivedData; // String containing data read from COM3 port

    public Animator doorAnim;   // Doors animator component
    public MeshRenderer screen; // Screen 3D object of door reader
    public Material neutralMat; // Screen material in neutral state
    public Material greenMat; // Screen material if access is authorized
    public Material redMat; // Screen material if acces is denied
    bool cardRead;  // Bool to monitor if card is read
    float timer = 0;    // Timer of card reader

    // Start is called before the first frame update
    void Start()
    {
        dataStream.Open();  // Open serial port COM3
        dataStream.DtrEnable = true;
        dataStream.ReadTimeout = 10;
    }

    // Update is called once per frame
    void Update()
    {
        if (cardRead)
        {
            print(timer);
            timer += Time.deltaTime;
            if (timer > 2)
            {
                // If card was read, change screen material to neutral after 2s
                screen.material = neutralMat;
                cardRead = false;
                timer = 0;
            }
        }

        receivedData = dataStream.ReadLine();   // Read data from serial port
        if (receivedData == "Authorized access")
        {
            screen.material = greenMat;
            cardRead = true;
            doorAnim.enabled = true;
        }
        else if (receivedData == "Access denied")
        {
            screen.material = redMat;
            cardRead = true;
        }
    }
}

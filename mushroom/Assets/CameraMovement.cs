using UnityEngine;
using UnityEngine.UI;

public class CameraMovement : MonoBehaviour
{
    public float moveSpeed = 50f;
    private float shiftMultiplier;
    public float scrollSpeed = 250f;
    public float rotateSpeed = 150f;
    public Text pText;
    public Text rText;
    public GameObject player;
    public GameObject flag;

    private void Start()
    {

    }
    void FixedUpdate()
    {
        if (player.transform.position.x - 91 < 1 && player.transform.position.x - 91 > 0 && player.transform.position.y - 76 < 1 && player.transform.position.y - 76 > 0 && player.transform.position.z < 1 && player.transform.position.z > -2)
        {
            flag.SetActive(true);
        }
        else
        {
            flag.SetActive(false);
        }
        pText.text = "Position: " + player.transform.position;
        rText.text = "Rotation: " + player.transform.rotation;

        shiftMultiplier = Input.GetKey("1") ? 1f : 0.01f;

        if (Input.GetKey("t") && Input.GetKey("u") && Input.GetKey("r") && Input.GetKey("n")) {

            rotateSpeed = 100;
            Debug.Log("A");
        }

        if (Input.GetKey("w"))
        {
            transform.Translate(Vector3.forward * moveSpeed * shiftMultiplier * Time.deltaTime / Time.timeScale);
        }
        if (Input.GetKey("s"))
        {
            transform.Translate(Vector3.back * moveSpeed * shiftMultiplier * Time.deltaTime / Time.timeScale);
        }
        if (Input.GetKey("a"))
        {
            transform.Translate(Vector3.left * moveSpeed * shiftMultiplier * Time.deltaTime / Time.timeScale);
        }
        if (Input.GetKey("d"))
        {
            transform.Translate(Vector3.right * moveSpeed * shiftMultiplier * Time.deltaTime / Time.timeScale);
        }

        GetComponent<Camera>().fieldOfView -= Input.GetAxis("Mouse ScrollWheel") * scrollSpeed * Time.deltaTime / Time.timeScale;
        GetComponent<Camera>().fieldOfView = Mathf.Clamp(GetComponent<Camera>().fieldOfView, 30, 90);


        if (Input.GetMouseButton(1))
        {
            //Clamp this
            transform.eulerAngles += rotateSpeed * new Vector3(-Input.GetAxis("Mouse Y"), Input.GetAxis("Mouse X"), 0) * Time.deltaTime / Time.timeScale;
            Cursor.lockState = CursorLockMode.Locked;
        }
        else
        {
            Cursor.lockState = CursorLockMode.None;
        }
    }
}
using UnityEngine;
using System.Collections;
using System.IO;
using UnityEditor;

public class XML_Exporter : EditorWindow {

	public GameObject[] GameObjects;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	[MenuItem("Tools/XML Exporter")] 
	static void Init()
	{
		//Create new window
		XML_Exporter windowLevel = (XML_Exporter)EditorWindow.GetWindow(typeof(XML_Exporter));
	}

	void OnGUI()
	{
		if (GUILayout.Button("Export XML Stuff", GUILayout.Width(255)))
		{
			using (FileStream stream = File.Create("output.xml"))
			{
				using (StreamWriter writer = new StreamWriter(stream))
				{
					GameObjects = GameObject.FindGameObjectsWithTag("Cubes");
					foreach (GameObject obj in GameObjects)
					{
						writer.Write("<Cube>\n");
						writer.Write("\t<Position x=\"" + obj.transform.position.x + "\" y=\"" + obj.transform.position.y + "\" z=\"" + obj.transform.position.z + "\"/>\n");
						writer.Write("\t<Scale x=\"" + obj.transform.localScale.x + "\" y=\"" + obj.transform.localScale.y + "\" z=\"" + obj.transform.localScale.z + "\"/>\n");
						writer.Write("\t<Rotation x=\"" + obj.transform.localRotation.eulerAngles.x + "\" y=\"" + obj.transform.eulerAngles.y + "\" z=\"" + obj.transform.eulerAngles.z + "\"/>\n");
						writer.Write("</Cube>\n");
					}
				}
			}
		}
	}
}

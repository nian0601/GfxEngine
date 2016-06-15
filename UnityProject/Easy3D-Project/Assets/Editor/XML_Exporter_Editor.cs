using UnityEngine;
using UnityEditor;
using System.Collections;
using System.IO;

[CustomEditor(typeof(XML_Exporter))]
public class XML_Exporter_Editor : Editor
{
    public GameObject[] GameObjects;

    public override void OnInspectorGUI()
    {
        GUILayout.BeginHorizontal();
        GUILayout.Label(" Grid Width ");
        EditorGUILayout.FloatField(5, GUILayout.Width(50));
        GUILayout.EndHorizontal();

        if (GUILayout.Button("Export XML Stuff", GUILayout.Width(255)))
        {
            using (FileStream stream = File.Create("output.xml"))
            {
				using (StreamWriter writer = new StreamWriter(stream))
				{
					GameObjects = GameObject.FindGameObjectsWithTag("Cubes");
					foreach (GameObject obj in GameObjects)
					{
						//StringWriter ss = new StringWriter();
						
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

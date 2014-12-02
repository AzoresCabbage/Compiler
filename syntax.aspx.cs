using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.IO;

public partial class syntax : System.Web.UI.Page
{
    static string rootpath = @"C:\Users\coolwyj\Documents\Visual Studio 2012\WebSites\WebSite1\";
    public string value="";

    protected void Page_Load(object sender, EventArgs e)
    {
        StreamReader sr = new StreamReader(rootpath + "syntax_grammar.txt");
        value = sr.ReadToEnd();
        sr.Close();

        if (Request.Form["s"] == "1")
        {
            string syntax = Request.Form["syntax"].ToString();
            //syntax = Server.UrlDecode(syntax);

            FileStream fs = new FileStream(rootpath + "syntax_grammar.txt", FileMode.Create, FileAccess.Write);
            //初始化写入流对象，指定要写入的流，编码方式
            StreamWriter sw = new StreamWriter(fs, System.Text.Encoding.Default);
            //向文件写入内容
            sw.WriteLine(syntax);
            //关闭流
            sw.Close();
            fs.Close();

            Response.Write(syntax);
            Response.End();
        }
    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        Response.Redirect("Default.aspx");
    }
}
<%@ Page Language="C#" AutoEventWireup="true" CodeFile="lex.aspx.cs" Inherits="lex" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <link rel="stylesheet" href="/css/docs.css" />
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <article>
            <p>
                当前词法文件：
            </p>
            <textarea id="curLex" cols="20" rows="2" style="resize: none; width: 590px; height: 440px" readonly="readonly"><%=value %></textarea>
            <p>
                双击文本框编辑词法
            </p>

            <p>
                <script type="text/javascript">
                    function ajax() {
                        lex.readOnly = true;
                        var xmlhttp;
                        if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
                            xmlhttp = new XMLHttpRequest();
                        }
                        else {// code for IE6, IE5
                            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                        }
                        xmlhttp.onreadystatechange = function () {
                            if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                                document.getElementById("curLex").innerHTML = xmlhttp.responseText;
                            }
                        }
                        var str = document.getElementById("curLex").value;
                        str = "s=1&lex=" + encodeURIComponent(str);
                        xmlhttp.open("POST", "lex.aspx", true);
                        xmlhttp.setRequestHeader("content-type", "application/x-www-form-urlencoded");//post提交设置项
                        xmlhttp.send(str);
                    }
                </script>
                <button id="updateLex" type="button" class="button" onclick="ajax()">更新词法</button>
                <asp:Button ID="Button1" runat="server" Text="返回" OnClick="Button1_Click" CssClass="button" />
            </p>
            <script type="text/javascript">
                var lex = document.getElementById("curLex");
                lex.ondblclick = function () {
                    this.readOnly = false;
                }
                lex.onblur = function () {
                    this.readOnly = true;
                }
            </script>
        </article>
        
    </div>
    </form>
</body>
</html>

<%@ Page Language="C#" AutoEventWireup="true" CodeFile="syntax.aspx.cs" Inherits="syntax" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link rel="stylesheet" href="/css/docs.css" />
    <link rel="stylesheet" href="/css/show-hint.css" />
    <link rel="stylesheet" href="/css/codemirror.css" />
    <link rel="stylesheet" href="/css/fullscreen.css"/>
    
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <article>
              
                <p>
                    当前语法文件：
                </p>
                <textarea id="curSyntax" cols="20" rows="2" style="resize: none; width: 590px; height: 440px" readonly="readonly"><%=value %></textarea>
                <p>
                    双击文本框编辑语法
                </p>
                <p>
                    <script type="text/javascript">
                        function loadXMLDoc() {
                            Syn.readOnly = true;
                            var xmlhttp;
                            if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
                                xmlhttp = new XMLHttpRequest();
                            }
                            else {// code for IE6, IE5
                                xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                            }
                            xmlhttp.onreadystatechange = function () {
                                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                                    document.getElementById("curSyntax").innerHTML = xmlhttp.responseText;
                                }
                            }
                            var str = document.getElementById("curSyntax").value;
                            str = "s=1&syntax="+encodeURIComponent(str);
                            xmlhttp.open("POST", "syntax.aspx", true);
                            xmlhttp.setRequestHeader("content-type", "application/x-www-form-urlencoded");//post提交设置项
                            xmlhttp.send(str);
                        }
                    </script>
                    <button id="updateSyn" type="button" class="button" onclick="loadXMLDoc()">更新语法</button>
                    <asp:Button ID="Button1" runat="server" Text="返回" OnClick="Button1_Click" CssClass="button" />
                </p>
                <script type="text/javascript">
                    var Syn = document.getElementById("curSyntax");
                    Syn.ondblclick = function () {
                        this.readOnly = false;
                    }
                    Syn.onblur = function () {
                        this.readOnly = true;
                    }
                </script>
            </article>
        </div>
    </form>
</body>
</html>

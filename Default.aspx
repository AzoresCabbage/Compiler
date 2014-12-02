<%@ Page Language="C#"  ValidateRequest="false" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="/css/docs.css" />
    <link rel="stylesheet" href="/css/show-hint.css" />
    <link rel="stylesheet" href="/css/codemirror.css" />
    <link rel="stylesheet" href="/css/fullscreen.css"/>

    <link rel="stylesheet" href="../theme/3024-day.css"/>
    <link rel="stylesheet" href="../theme/3024-night.css"/>
    <link rel="stylesheet" href="../theme/ambiance.css"/>
    <link rel="stylesheet" href="../theme/base16-dark.css"/>
    <link rel="stylesheet" href="../theme/base16-light.css"/>
    <link rel="stylesheet" href="../theme/blackboard.css"/>
    <link rel="stylesheet" href="../theme/cobalt.css"/>
    <link rel="stylesheet" href="../theme/eclipse.css"/>
    <link rel="stylesheet" href="../theme/elegant.css"/>
    <link rel="stylesheet" href="../theme/erlang-dark.css"/>
    <link rel="stylesheet" href="../theme/lesser-dark.css"/>
    <link rel="stylesheet" href="../theme/mbo.css"/>
    <link rel="stylesheet" href="../theme/mdn-like.css"/>
    <link rel="stylesheet" href="../theme/midnight.css"/>
    <link rel="stylesheet" href="../theme/monokai.css"/>
    <link rel="stylesheet" href="../theme/neat.css"/>
    <link rel="stylesheet" href="../theme/neo.css"/>
    <link rel="stylesheet" href="../theme/night.css"/>
    <link rel="stylesheet" href="../theme/paraiso-dark.css"/>
    <link rel="stylesheet" href="../theme/paraiso-light.css"/>
    <link rel="stylesheet" href="../theme/pastel-on-dark.css"/>
    <link rel="stylesheet" href="../theme/rubyblue.css"/>
    <link rel="stylesheet" href="../theme/solarized.css"/>
    <link rel="stylesheet" href="../theme/the-matrix.css"/>
    <link rel="stylesheet" href="../theme/tomorrow-night-eighties.css"/>
    <link rel="stylesheet" href="../theme/twilight.css"/>
    <link rel="stylesheet" href="../theme/vibrant-ink.css"/>
    <link rel="stylesheet" href="../theme/xq-dark.css"/>
    <link rel="stylesheet" href="../theme/xq-light.css"/>


    <script src="/js/codemirror.js"></script>
    <script src="/js/matchbrackets.js"></script>
    <script src="/js/show-hint.js"></script>
    <script src="/js/clike.js"></script>
    <script src="/js/active-line.js"></script>
    <script src="/js/fullscreen.js"></script>



    <style>
        .CodeMirror {
            border: 2px inset #dee;
        }
        #TextArea1 {
            width: 590px;
            height: 145px;
        }
        #Info {
            height: 150px;
            width: 593px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server" method="post">
        <div>

            <article>

                <p>
                    <textarea id="code" name="code"></textarea>
                </p>

                <p>
                  选择一种语法高亮主题:
                    <select onchange="selectTheme()" id="select">
                        <option selected="selected">default</option>
                        <option>3024-day</option>
                        <option>3024-night</option>
                        <option>ambiance</option>
                        <option>base16-dark</option>
                        <option>base16-light</option>
                        <option>blackboard</option>
                        <option>cobalt</option>
                        <option>eclipse</option>
                        <option>elegant</option>
                        <option>erlang-dark</option>
                        <option>lesser-dark</option>
                        <option>mbo</option>
                        <option>mdn-like</option>
                        <option>midnight</option>
                        <option>monokai</option>
                        <option>neat</option>
                        <option>neo</option>
                        <option>night</option>
                        <option>paraiso-dark</option>
                        <option>paraiso-light</option>
                        <option>pastel-on-dark</option>
                        <option>rubyblue</option>
                        <option>solarized dark</option>
                        <option>solarized light</option>
                        <option>the-matrix</option>
                        <option>tomorrow-night-eighties</option>
                        <option>twilight</option>
                        <option>vibrant-ink</option>
                        <option>xq-dark</option>
                        <option>xq-light</option>
                    </select>
                </p>

                <p>
                    光标处于编辑器中时，按下 <strong>F11</strong> 开启全屏编辑
                </p>

                <script>
                    var editor = CodeMirror.fromTextArea(document.getElementById("code"), {
                        lineNumbers: true,
                        styleActiveLine: true,
                        matchBrackets: true,
                        mode: "text/x-csrc",
                        extraKeys: {
                            "F11": function (cm) {
                                cm.setOption("fullScreen", !cm.getOption("fullScreen"));
                            },
                            "Esc": function (cm) {
                                if (cm.getOption("fullScreen")) cm.setOption("fullScreen", false);
                            }
                        }
                    });

                    var mac = CodeMirror.keyMap.default == CodeMirror.keyMap.macDefault;
                    CodeMirror.keyMap.default[(mac ? "Cmd" : "Ctrl") + "-Space"] = "autocomplete";

                    var input = document.getElementById("select");
                    function selectTheme() {
                        var theme = input.options[input.selectedIndex].innerHTML;
                        editor.setOption("theme", theme);
                    }
                    var choice = document.location.search &&
                                 decodeURIComponent(document.location.search.slice(1));
                    if (choice) {
                        input.value = choice;
                        editor.setOption("theme", choice);
                    }

                </script>
                <p>
                    <script type="text/javascript">
                        function loadXMLDoc() {
                            var xmlhttp;
                            if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
                                xmlhttp = new XMLHttpRequest();
                            }
                            else {// code for IE6, IE5
                                xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                            }
                            xmlhttp.onreadystatechange = function () {
                                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                                    document.getElementById("Info").innerHTML = xmlhttp.responseText;//decodeURIComponent(xmlhttp.responseText);
                                    document.getElementById("analyzebtn").disabled = false;
                                    document.getElementById("analyzebtn").innerHTML = "开始分析";
                                }
                                else {
                                    document.getElementById("analyzebtn").innerHTML = "分析中……";
                                    document.getElementById("analyzebtn").disabled = true;
                                }
                            }
                            var str = editor.getValue().toString();
                            str = "s=1&code="+encodeURIComponent(str);
                            xmlhttp.open("POST", "Default.aspx", true);
                            xmlhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
                            xmlhttp.send(str);
                        }
                    </script>
                    <button id="analyzebtn" type="button" class="button" onclick="loadXMLDoc()">开始分析</button>
                    <asp:Button ID="Button2" CssClass="button" runat="server" Text="查看词法" OnClick="Button2_Click" />
                    <asp:Button ID="Button1" CssClass="button" runat="server" Text="查看语法" OnClick="Button1_Click" />
                </p>
                <div>
                    <textarea id="Info" name="S1" readonly="readonly" style="resize:none"></textarea>

                </div>
            </article>
            

        </div>
    </form>
</body>
</html>
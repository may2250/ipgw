/*
   Generated from client/login.esp
 */
#include "esp.h"

static void view_180e091f150879e8006e14b565bb0006(HttpConn *conn) {
  espRenderBlock(conn, "<!DOCTYPE html>\r\n\
<html lang=\"en\">\r\n\
<head>\r\n\
    <title>数字网管---登录</title>\r\n\
    <meta charset=\"utf-8\" />\r\n\
    <link rel=\"icon\" href=\"img/favicon.ico\" type=\"image/x-icon\">    \r\n\
    <link rel=\"stylesheet\" href=\"css/all.css\" type=\"text/css\">\r\n\
</head>\r\n\
<body>\r\n\
    <div id=\"wrapper\">	\r\n\
		<div id=\"login\" class=\"animate form\">\r\n\
				<h1>用户登录</h1> \r\n\
				<p> \r\n\
					<label class=\"uname\" > 用户名 </label>\r\n\
					<input class=\"username\" required=\"required\" type=\"text\" autocomplete=\"off\" value='' placeholder=\"请输入用户名\"/>\r\n\
				</p>\r\n\
				<p> \r\n\
					<label for=\"password\" class=\"youpasswd\"> 密码 </label>\r\n\
					<input class=\"password\" required=\"required\" type=\"password\" autocomplete=\"off\" value='' placeholder=\"请输入密码\" />\r\n\
				</p>\r\n\
				<p class=\"keeplogin\"> \r\n\
					<input type=\"checkbox\" class=\"loginkeeping\" value=\"loginkeeping\" />\r\n\
					<label>记住密码</label>\r\n\
				</p>\r\n\
				<p class=\"login button\"> \r\n\
					<input type=\"button\" class=\"btn_submit\" value=\"登录\" />\r\n\
				</p>\r\n\
		</div>\r\n\
		\r\n\
    </div>   \r\n\
	<div class=\"footer\">\r\n\
		<hr/>\r\n\
		<p>© Prevail Software, 2014-2024. All rights reserved.</p>\r\n\
	</div>\r\n\
	<script type=\"text/javascript\" src=\"lib/jquery.min.js\"></script>\r\n\
    <script type=\"text/javascript\">\r\n\
        var localip = window.location.href.substr(7, window.location.href.indexOf(':', 7) - 7);\r\n\
		var isremember = localStorage.getItem(\"remember\");\r\n\
		if(isremember == undefined || isremember == \"\" || isremember == \"false\"){\r\n\
			localStorage.setItem(\"remember\", false);\r\n\
			$('.password').val(\"\");\r\n\
		}else{\r\n\
			$('.password').val(localStorage.getItem(\"password\"));\r\n\
			$('.loginkeeping')[0].checked = true;\r\n\
		}\r\n\
		$('.username').val(localStorage.getItem(\"username\"));\r\n\
		\r\n\
		$('.loginkeeping').click(function(){\r\n\
			isremember = $('.loginkeeping')[0].checked;\r\n\
			localStorage.setItem(\"username\", $('.username')[0].value);\r\n\
			if(isremember){\r\n\
				localStorage.setItem(\"remember\",true);\r\n\
				localStorage.setItem(\"password\", $('.password')[0].value);\r\n\
			}else{\r\n\
				localStorage.setItem(\"remember\",false);\r\n\
				localStorage.setItem(\"password\", \"\");\r\n\
			}\r\n\
		});\r\n\
		\r\n\
		$('.btn_submit').click(function(){\r\n\
		    $('.username').removeClass(\"inputerror\");\r\n\
		    $('.password').removeClass(\"inputerror\");\r\n\
		    var jsonstr = '{\"username\":\"' + $('.username').val() + '\",\"password\":\"'+$('.password').val() + '\"}';\r\n\
		    $.ajax({\r\n\
                type: \"GET\",\r\n\
                async:false,\r\n\
                url: \"http://\"+localip+\":4000/do/login/check\",\r\n\
                data: JSON.parse(jsonstr),\r\n\
                dataType: \"json\",\r\n\
                timeout : 5000,\r\n\
                success: function(data){\r\n\
                    if(data.sts == 0){\r\n\
                        localStorage.setItem(\"username\", $('.username')[0].value);\r\n\
                        if(isremember){\r\n\
                            localStorage.setItem(\"remember\",true);\r\n\
                            localStorage.setItem(\"password\", $('.password')[0].value);\r\n\
                        }\r\n\
                        window.location.href=\"http://\"+localip+\":4000/index.esp\";\r\n\
                    }else if(data.sts == 1){\r\n\
                        $('.username').addClass(\"inputerror\");\r\n\
                        alert(\"用户名不存在!\");\r\n\
                    }else if(data.sts == 2){\r\n\
                        $('.password').addClass(\"inputerror\");\r\n\
                        alert(\"密码错误!\");\r\n\
                    }\r\n\
                },\r\n\
                error : function(err) {\r\n\
\r\n\
                }\r\n\
            });\r\n\
		});\r\n\
		\r\n\
    </script> \r\n\
</body>\r\n\
</html>\r\n\
", 3583);
}

ESP_EXPORT int esp_view_180e091f150879e8006e14b565bb0006(HttpRoute *route, MprModule *module) {
   espDefineView(route, "client/login.esp", view_180e091f150879e8006e14b565bb0006);
   return 0;
}

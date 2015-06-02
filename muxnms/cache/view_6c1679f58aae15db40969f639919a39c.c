/*
   Generated from client/index.esp
 */
#include "esp.h"

static void view_6c1679f58aae15db40969f639919a39c(HttpConn *conn) {
  espRenderBlock(conn, "<!DOCTYPE html>\n\
<html lang=\"en\">\n\
<head>\n\
    <title>数字网管</title>\n\
    <meta charset=\"utf-8\" />\n\
    <link rel=\"icon\" href=\"img/favicon.ico\" type=\"image/x-icon\">    \n\
    <link rel=\"stylesheet\" href=\"css/ui.fancytree.min.css\" type=\"text/css\"> \n\
    <link rel=\"stylesheet\" href=\"css/jquery-ui.min.css\" type=\"text/css\">\n\
    <link rel=\"stylesheet\" href=\"css/jquery.dataTables.min.css\" type=\"text/css\">\n\
    <link rel=\"stylesheet\" href=\"css/all.css\" type=\"text/css\">\n\
</head>\n\
<body>\n\
	<div class=\"navbar\">\n\
		<nav>\n\
			<label>数字设备网管</label>\n\
		</nav>\n\
    </div>\n\
    <div class=\"container\">\n\
		<div class=\"l-sidebar\">	  \n\
			<div class=\"ny_zb\">\n\
				<div class=\"ny_zblb1\">\n\
					<ul class=\"clearfix\">\n\
						<li id=\"l1\">\n\
							<a class=\"cur STRING_BASE\" href=\"javascript:toHome()\"><strong>节目列表</strong></a>\n\
						</li>\n\
						<li class=\"subs\" id=\"l2\">\n\
							<a class=\"flag STRING_DETAIL\" href=\"javascript:void(0)\"><strong>发送源</strong></a>\n\
						</li>\n\
						<li class=\"subs\" id=\"l3\">\n\
							<a class=\"flag STRING_NETSET\" href=\"javascript:void(0)\"><strong>设备功能</strong></a>\n\
						</li>\n\
						<li class=\"subs\" id=\"l4\">\n\
							<a class=\"flag STRING_MDEVICE\" href=\"javascript:void(0)\"><strong>设备管理</strong></a>\n\
							<ul>\n\
                                <li id=\"l41\"><a href=\"javascript:gbl_setIp()\">IP地址设置</a></li>\n\
                                <li id=\"l42\"><a href=\"javascript:gbl_reset()\">恢复出厂设置</a></li>\n\
                                <li id=\"l43\"><a href=\"javascript:gbl_restart()\">重启设备</a></li>\n\
                                <li id=\"l44\"><a href=\"javascript:gbl_password()\">修改密码</a></li>\n\
                            </ul>\n\
                        </li>\n\
                        <li class=\"subs\" id=\"l5\">\n\
                            <a class=\"flag STRING_LOG\" href=\"javascript:void(0)\"><strong>日志记录</strong></a>\n\
                            <ul>\n\
                                <li id=\"l51\"><a href=\"javascript:alarm_output(2)\">操作日志</a></li>\n\
                             </ul>\n\
                         </li>\n\
                         <li id=\"l6\">\n\
                            <!-- <a href=\"javascript:void(0)\" class=\"STRING_HELP\"><strong>帮助</strong></a> -->\n\
                         </li>\n\
                         <li id=\"l7\">\n\
                             <a href=\"javascript:btn_close()\" class=\"STRING_EXIT\"><strong>退出</strong></a>\n\
                         </li>\n\
                     </ul>\n\
                 </div>\n\
\n\
             </div>\n\
         </div>\n\
         <div class=\"main-content\">\n\
             <!--  CONTENT  -->\n\
		</div>\n\
    </div>\n\
	<div class=\"footer\">\n\
		<hr/>\n\
		<p> ", 2666);
  espRenderSafeString(conn, mprGetDate(0));
  espRenderBlock(conn, "</p>\n\
		<p>© Prevail Software, 2014-2024.V0.1.0 All rights reserved.</p>\n\
	</div>\n\
    <script type=\"text/javascript\" src=\"lib/jquery.min.js\"></script>\n\
    <script type=\"text/javascript\" src=\"lib/jquery-ui.min.js\"></script>\n\
    <script type=\"text/javascript\" src=\"lib/jquery.fancytree.min.js\"></script>    \n\
    <script type=\"text/javascript\" src=\"lib/jquery.dataTables.min.js\"></script>\n\
	<script type=\"text/javascript\" src=\"js/global.js\"></script> \n\
	<script type=\"text/javascript\" src=\"js/alarm.js\"></script> \n\
	<script type=\"text/javascript\" src=\"js/devinfo.js\"></script>\n\
	<script src=\"lib/jquery.popup.js\" type=\"text/javascript\"></script>\n\
	<script src=\"lib/jquery.fancytree.menu.js\" type=\"text/javascript\"></script>\n\
    <script type=\"text/javascript\">		\n\
		var localip = window.location.href.substr(7, window.location.href.indexOf(':', 7) - 7);\n\
		var os = getOS();\n\
		function getOS(){\n\
            var str=navigator.userAgent;\n\
            var BrowserS=['MSIE 9.0','MSIE 8.0','MSIE 7.0','MSIE6.0',\n\
                'Firefox','Opera','Chrome'];\n\
            for(var i=0;i<BrowserS.length;i++){\n\
                if(str.indexOf(BrowserS[i])>=0){return BrowserS[i].replace('MSIE','IE');}\n\
            }\n\
		}\n\
\n\
		function btn_close() {\n\
			var userAgent = navigator.userAgent;\n\
			//注销				\n\
			$.ajax({\n\
				 type: \"GET\",\n\
				 async:false,\n\
				 url: \"http://\"+localip+\":4000/do/login/logout\",\n\
				 dataType: \"text\",\n\
				 success: function(data){\n\
					\n\
				 },    \n\
				 error : function(err) {    \n\
   \n\
				 }   \n\
			});\n\
			if (userAgent.indexOf(\"Firefox\") != -1 || userAgent.indexOf(\"Presto\") != -1) {\n\
				window.location.replace(\"about:blank\");\n\
			} else {\n\
				window.opener = null;\n\
				window.open(\"\", \"_self\");\n\
				window.close();\n\
			}\n\
		}\n\
		\n\
		$(function(){						\n\
			$(\".ny_zblb1 ul li\").click(function(){\n\
				var thisSpan=$(this);\n\
				$(\".ny_zblb1 a\").removeClass(\"cur\");\n\
				$(this).children(\"a\").addClass(\"cur\");\n\
				$(this).children(\"ul\").slideDown(\"fast\");\n\
				$(this).siblings().children(\"ul\").slideUp(\"fast\");\n\
			});\n\
		});\n\
    </script> \n\
</body>\n\
</html>\n\
", 2048);
}

ESP_EXPORT int esp_view_6c1679f58aae15db40969f639919a39c(HttpRoute *route, MprModule *module) {
   espDefineView(route, "client/index.esp", view_6c1679f58aae15db40969f639919a39c);
   return 0;
}

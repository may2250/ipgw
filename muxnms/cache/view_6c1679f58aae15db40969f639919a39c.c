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
                            <a class=\"cur STRING_BASE\" href=\"javascript:toHome()\"><strong>基本信息</strong></a>\n\
                        </li>\n\
						<li id=\"l2\">\n\
							<a class=\"cur STRING_BASE\" href=\"javascript:createHomeUI()\"><strong>节目列表</strong></a>\n\
						</li>\n\
						<li class=\"subs\" id=\"l3\">\n\
							<a class=\"flag STRING_DETAIL\" href=\"javascript:createSendSrcUI()\"><strong>发送源</strong></a>\n\
						</li>\n\
						<li class=\"subs\" id=\"l4\">\n\
							<a class=\"flag STRING_NETSET\" href=\"javascript:void(0)\"><strong>设备功能</strong></a>\n\
						</li>\n\
						<li class=\"subs\" id=\"l5\">\n\
							<a class=\"flag STRING_MDEVICE\" href=\"javascript:void(0)\"><strong>设备管理</strong></a>\n\
							<ul>\n\
                                <li id=\"l51\"><a href=\"javascript:gbl_setIp()\">IP地址设置</a></li>\n\
                                <li id=\"l52\"><a href=\"javascript:gbl_reset()\">恢复出厂设置</a></li>\n\
                                <li id=\"l53\"><a href=\"javascript:gbl_restart()\">重启设备</a></li>\n\
                                <li id=\"l54\"><a href=\"javascript:gbl_password()\">修改密码</a></li>\n\
                            </ul>\n\
                        </li>\n\
                        <li class=\"subs\" id=\"l6\">\n\
                            <a class=\"flag STRING_LOG\" href=\"javascript:void(0)\"><strong>日志记录</strong></a>\n\
                            <ul>\n\
                                <li id=\"l61\"><a href=\"javascript:alarm_output(2)\">操作日志</a></li>\n\
                             </ul>\n\
                         </li>\n\
                         <li id=\"l7\">\n\
                            <!-- <a href=\"javascript:void(0)\" class=\"STRING_HELP\"><strong>帮助</strong></a> -->\n\
                         </li>\n\
                         <li id=\"l8\">\n\
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
		<p> ", 2865);
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
        var recdata;\n\
		var os = getOS();\n\
		function getOS(){\n\
            var str=navigator.userAgent;\n\
            var BrowserS=['MSIE 9.0','MSIE 8.0','MSIE 7.0','MSIE6.0',\n\
                'Firefox','Opera','Chrome'];\n\
            for(var i=0;i<BrowserS.length;i++){\n\
                if(str.indexOf(BrowserS[i])>=0){return BrowserS[i].replace('MSIE','IE');}\n\
            }\n\
		}\n\
        //获取设备基本信息\n\
//        $.ajax({\n\
//            type: \"GET\",\n\
//            async:false,\n\
//            url: \"http://\"+localip+\":4000/do/programs/getDevinfo\",\n\
//            dataType: \"json\",\n\
//            success: function(data){\n\
//                if(data.sts == 8){\n\
//                    window.location = \"/login.esp\";\n\
//                }\n\
//                recdata = data;\n\
//            },\n\
//            error : function(err,b,c) {\n\
//                if(err.responseText == \"login.esp\"){\n\
//                    window.location = \"/login.esp\";\n\
//                }\n\
//            }\n\
//        });\n\
//        $('.main-content').empty();\n\
//        $('.main-content').append(\n\
//                '<table id=\"basedev\" class=\"tbl_baseinfo\" cellspacing=\"0\" width=\"100%\">'\n\
//                +'<tbody>'\n\
//                +'<tr>'\n\
//                +'<th><label>名称:</label></th>'\n\
//                +'<th><label id=\"dev-name\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>类型:</label></th>'\n\
//                +'<th><label id=\"dev-type\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>有效性:</label></th>'\n\
//                +'<th><label id=\"dev-valid\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>链接方式:</label></th>'\n\
//                +'<th><label id=\"dev-connect\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>网络地址:</label></th>'\n\
//                +'<th><label id=\"dev-ip\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>端口号:</label></th>'\n\
//                +'<th><label id=\"dev-port\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>硬件版本:</label></th>'\n\
//                +'<th><label id=\"dev-biosversion\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>软件版本:</label></th>'\n\
//                +'<th><label id=\"dev-softversion\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'<tr>'\n\
//                +'<th><label>固件版本:</label></th>'\n\
//                +'<th><label id=\"dev-firmware\" class=\"tbl_th\">T</label></th>'\n\
//                +'</tr>'\n\
//                +'</tbody>'\n\
//                +'</table>'\n\
//        );\n\
//\n\
//        function toHome() {\n\
//            if(globalObj.timerID != undefined){\n\
//                clearInterval(globalObj.timerID);\n\
//            }\n\
//            //获取设备基本信息\n\
//            $.ajax({\n\
//                type: \"GET\",\n\
//                async:false,\n\
//                url: \"http://\"+localip+\":4000/do/programs/getDevinfo\",\n\
//                dataType: \"json\",\n\
//                success: function(data){\n\
//                    recdata = data;\n\
//                },\n\
//                error : function(err) {\n\
//                }\n\
//            });\n\
//            //\n\
//            //\n\
//            $('.main-content').empty();\n\
//            $('.main-content').append(\n\
//                    '<table id=\"basedev\" class=\"tbl_baseinfo\" cellspacing=\"0\" width=\"100%\">'\n\
//                    +'<tbody>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>名称:</label></th>'\n\
//                    +'<th><label id=\"dev-name\" class=\"tbl_th\">T'+recdata.IP+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>类型:</label></th>'\n\
//                    +'<th><label id=\"dev-type\" class=\"tbl_th\">'+recdata.devType+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>有效性:</label></th>'\n\
//                    +'<th><label id=\"dev-valid\" class=\"tbl_th\">是</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>链接方式:</label></th>'\n\
//                    +'<th><label id=\"dev-connect\" class=\"tbl_th\">TCP</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>网络地址:</label></th>'\n\
//                    +'<th><label id=\"dev-ip\" class=\"tbl_th\">'+recdata.IP+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>端口号:</label></th>'\n\
//                    +'<th><label id=\"dev-port\" class=\"tbl_th\">'+recdata.port+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>硬件版本:</label></th>'\n\
//                    +'<th><label id=\"dev-biosversion\" class=\"tbl_th\">'+recdata.HardVersion+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>软件版本:</label></th>'\n\
//                    +'<th><label id=\"dev-softversion\" class=\"tbl_th\">'+recdata.SoftVersion+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'<tr>'\n\
//                    +'<th><label>固件版本:</label></th>'\n\
//                    +'<th><label id=\"dev-firmware\" class=\"tbl_th\">'+recdata.FpgaVersion+'</label></th>'\n\
//                    +'</tr>'\n\
//                    +'</tbody>'\n\
//                    +'</table>'\n\
//            );\n\
//        }\n\
//        try{\n\
//            $(\"#dev-name\")[0].textContent = \"T\"+recdata.IP;\n\
//            $(\"#dev-type\")[0].textContent = recdata.devType;\n\
//            $(\"#dev-valid\")[0].textContent = \"是\";\n\
//            $(\"#dev-connect\")[0].textContent = \"TCP\";\n\
//            $(\"#dev-ip\")[0].textContent = recdata.IP;\n\
//            $(\"#dev-port\")[0].textContent = recdata.port;\n\
//            $(\"#dev-biosversion\")[0].textContent = recdata.HardVersion;\n\
//            $(\"#dev-softversion\")[0].textContent = recdata.SoftVersion;\n\
//            $(\"#dev-firmware\")[0].textContent = recdata.FpgaVersion;\n\
//        }catch(err){\n\
//\n\
//        }\n\
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
", 8143);
}

ESP_EXPORT int esp_view_6c1679f58aae15db40969f639919a39c(HttpRoute *route, MprModule *module) {
   espDefineView(route, "client/index.esp", view_6c1679f58aae15db40969f639919a39c);
   return 0;
}

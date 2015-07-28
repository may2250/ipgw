function gbl_restart() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend class="i18n_RESTART">REBOOT</legend>'
				
				+'<div class="src_btn">'
					+'<button class="btn_restart i18n_RESTART">REBOOT</button>'
					+'<p class="gbltips"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	$.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_RESTART').html($.i18n.prop('RESTART'));           
            $('.i18n_RESTART')[1].textContent = $.i18n.prop('RESTART');
            
        }
    });
	$( ".btn_restart" ).button({
      icons: {
        primary: "ui-icon-power"
      }
    }).click(function( event ) {
        event.preventDefault();
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/reboot",
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.gbltips').empty();
                     $('.gbltips').append(globalObj._nv == "zh-CN"?"设备重启命令已下发，请30秒后尝试重新连接":"Device is Rebooting, pls waitting 30sec to reload....");
                 }else if(data.sts == 5){
                     alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                 }
			 },    
			 error : function(err) {   
				//alert("异常！====="+err);
			 }   
		});
	});
}

function gbl_reset() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend class="i18n_RESTOREDEFAULT">RESTORE DEFAULT</legend>'
				+'<div class="src_btn">'
					+'<button class="btn_reset i18n_RESTOREDEFAULT">RESTORE DEFAULT</button>'
					+'<p class="gbltips"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	$.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_RESTOREDEFAULT').html($.i18n.prop('RESTOREDEFAULT'));           
            $('.i18n_RESTOREDEFAULT')[1].textContent = $.i18n.prop('RESTOREDEFAULT');            
        }
    });
	$( ".btn_reset" ).button({
      icons: {
        primary: "ui-icon-refresh"
      }
    }).click(function( event ) {
        event.preventDefault();
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/reset",
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.gbltips').empty();
                     $('.gbltips').append(globalObj._nv == "zh-CN"?"恢复出厂设置命令已下发，请30秒后尝试重新连接":"Device restored, pls waitting 30secs to reload...");
                 }else if(data.sts == 5){
                     alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                 }else{
                     alert(globalObj._nv == "zh-CN"?"恢复出厂设置命令已下发异常，请30秒后尝试重新连接":"Device restored error, pls waitting 30secs to reload...");
                 }
			 },    
			 error : function(err) {   
				//alert("异常！====="+err);
			 }   
		});
	});
}

function gbl_setIp() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
	$('.main-content').empty();
	$('.main-content').append(
		'<div class="src_content">'
			+'<fieldset>'
				+'<legend class="i18n_NETSETTING">NETWORK SETTING</legend>'
				+'<div class="network_set">'
					+'<table class="nettable">'
						+'<tr>'
							+'<td><label class="i18n_NEWIP">New IP:</label></td>'
							+'<td><input type="text" value="" class="newip" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="ipvalidate i18n_ILLEGALIP">Invalid IP!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td><label class="i18n_NEWGATEWAY">New Gateway：</label></td>'
							+'<td><input type="text" value="" class="newgateway" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="gatewayvalidate i18n_ILLEGALGATEWAY">Invalid Gateway!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td><label class="i18n_NEWSUBMASK">New SubMask:</label></td>'
							+'<td><input type="text" value="" class="newsubmask" /></td>'
							+'<td><label style="display:none;width:150px;color:red;margin-right:20px" class="submaskvalidate i18n_ILLEGALSUBMASK">Invalid SubMask!!</label></td>'
						+'</tr>'
						+'<tr>'
							+'<td></td>'
							+'<td><button class="btn_set i18n_BTNCONFIG" style="float:right;margin:10px 30px">Config</button></td>'
							+'<td></td>'
						+'</tr>'
					+'</table>'
					+'<p class="settip"></p>'
				+'</div>'
			+'</fieldset>'
		+'</div>'
	);
	$.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_NETSETTING').html($.i18n.prop('NETSETTING'));
            $('.i18n_NEWIP').html($.i18n.prop('NEWIP'));
            $('.i18n_ILLEGALIP').html($.i18n.prop('ILLEGALIP'));
            $('.i18n_NEWGATEWAY').html($.i18n.prop('NEWGATEWAY'));
            $('.i18n_ILLEGALGATEWAY').html($.i18n.prop('ILLEGALGATEWAY'));
            $('.i18n_NEWSUBMASK').html($.i18n.prop('NEWSUBMASK'));            
            $('.i18n_ILLEGALSUBMASK').html($.i18n.prop('ILLEGALSUBMASK'));            
            $('.i18n_BTNCONFIG')[0].textContent = $.i18n.prop('BTNCONFIG');            
        }
    });
	$( ".btn_set" ).button({
      icons: {
        primary: "ui-icon-gear"
      }
    }).click(function( event ) {
        event.preventDefault();
		var re=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;//正则表达式
	    if(!re.test($(".newip").val()))
	    {
            $(".ipvalidate").css("display", "");
            return false;
	    }else{
            $(".ipvalidate").css("display", "none");
        }
		if(!re.test($(".newgateway").val()))
	    {
            $(".gatewayvalidate").css("display", "");
            return false;
        }else{
            $(".gatewayvalidate").css("display", "none");
        }
		if(!re.test($(".newsubmask").val()))
	    {
            $(".submaskvalidate").css("display", "");
            return false;
        }else{
            $(".submaskvalidate").css("display", "none");
        }

		$('.settip').empty();
		$('.settip').append(globalObj._nv == "zh-CN"?"设置命令已下发，请尝试重新连接":"Sending config, pls try to reload...");
		$.ajax({
			 type: "GET",
			 async:false,
			 url: "http://"+localip+":4000/do/globalopt/setDevip?"+$(".newip").val()+"&"+$(".newgateway").val()+"&"+$(".newsubmask").val(),
			 dataType: "json",
			 success: function(data){
                 if(data.sts == 1){
                     $('.settip').empty();
                     $('.settip').append(globalObj._nv == "zh-CN"?"设置命令已下发，请尝试重新连接":"Sending config, pls try to reload...");
                 }else if(data.sts == 5){
                     alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                 }
			 },
			 error : function(err) {
                 $('.settip').empty();
                 $('.settip').append(globalObj._nv == "zh-CN"?"下发失败，未知错误!":"Sending failed, unknown error!");
			 }
		});
	});
}

function gbl_password() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<fieldset>'
                +'<legend class="i18n_CHANGEPASSWORD">CHANGE PASSWORD</legend>'
                +'<div class="register_form">'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label class="i18n_OLDPASSWORD">Old Password</label></div>'
                        +'<div class="register_item rip"><input type="password" class="oldpassword" placeholder="password" /> </div>'
                    +'</div>'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label class="i18n_NEWPASSWORD">New Password</label></div>'
                        +'<div class="register_item rip"><input type="password" class="newpassword" placeholder="Password" /> </div>'
                    +'</div>'
                    +'<div class="register_formrow">'
                        +'<div class="register_item rlb"><label class="i18n_CONFIRMPASSWORD">Password Conform</label></div>'
                        +'<div class="register_item rip"><input type="password" class="cpassword" placeholder="Password" /> </div>'
                    +'</div>'
                +'</div>'
                +'<div class="src_btn">'
                    +'<button class="btn_submit i18n_MODIFY">Modify</button>'
                    +'<p></p>'
                +'</div>'
            +'</fieldset>'
        +'</div>'
    );
    $.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_CHANGEPASSWORD').html($.i18n.prop('CHANGEPASSWORD'));
            $('.i18n_OLDPASSWORD').html($.i18n.prop('OLDPASSWORD'));
            $('.i18n_NEWPASSWORD').html($.i18n.prop('NEWPASSWORD'));
            $('.i18n_CONFIRMPASSWORD').html($.i18n.prop('CONFIRMPASSWORD'));           
            $('.i18n_MODIFY')[0].textContent = $.i18n.prop('MODIFY');            
        }
    });
    $( ".btn_submit" ).button({
        icons: {
            primary: "ui-icon-gear"
        }
    }).click(function( event ) {
        event.preventDefault();
        if($(".newpassword").val() != $(".cpassword").val()){
            alert(globalObj._nv == "zh-CN"?"两次新密码输入不一致":"Two new password input is not consistent.");
            return;
        }
        if($(".oldpassword").val() == "" || $(".newpassword").val() == ""){
            alert(globalObj._nv == "zh-CN"?"密码不能为空.":"Password can not be null.");
            return;
        }
        var strjson = '{oldpassword:'+$(".oldpassword").val() + ',newpassword:'+ $(".newpassword").val()
            +  '}';
        $.ajax({
            type: "GET",
            async:false,
            url: "http://"+localip+":4000/do/globalopt/setPassword",
            data: strjson,
            dataType: "json",
            success: function(data){
                if(data.sts == 1){
                    $(".oldpassword").val("");
                    $(".newpassword").val("");
                    $(".cpassword").val("");
                    alert(globalObj._nv == "zh-CN"?"密码修改成功":"Password changed successful.");
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                }else if(data.sts == 0){
                    alert(globalObj._nv == "zh-CN"?"原密码输入不正确.":"Old password error.");
                }
            },
            error : function(err) {
                //alert("异常！====="+err);
            }
        });
    });
}

function gbl_upload() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'

                +'File:<input id="file1" type="file" name="file1">'

                +'<button id="sendfile" value="send"> send</button>'

        +'</div>'
    );
    
    function upload(input) {
      //支持chrome IE10
      if (window.FileReader) {
        var file = input.files[0];
        filename = file.name.split(".")[0];
        var reader = new FileReader();
        reader.onload = function() {
          console.log(this.result);
          alert(this.result);
          var paramjson = this.result;
          //post file content
          $.ajax({
                type: "GET",
                async: false,
                url: "http://"+localip+":4000/do/programs/uploads",
                data: JSON.parse(paramjson),
                dataType: "json",
                success: function(data){
                    if(data.sts == 8){
                        window.location = "/login.esp";
                    }else if(data.sts == 5){
                        alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                        return false;
                    }
                    
                },
                error : function(err) {
                    alert("AJAX ERROR---uploads!!");
                }
            });
        }
        reader.readAsText(file);
      } 
      //支持IE 7 8 9 10
      else if (typeof window.ActiveXObject != 'undefined'){
        var xmlDoc; 
        xmlDoc = new ActiveXObject("Microsoft.XMLDOM"); 
        xmlDoc.async = false; 
        xmlDoc.load(input.value); 
        var paramjson = xmlDoc.xml;
        //post file content
          $.ajax({
                type: "GET",
                async: false,
                url: "http://"+localip+":4000/do/programs/uploads",
                data: JSON.parse(paramjson),
                dataType: "json",
                success: function(data){
                    if(data.sts == 8){
                        window.location = "/login.esp";
                    }else if(data.sts == 5){
                        alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                        return false;
                    }
                    
                },
                error : function(err) {
                    alert("AJAX ERROR---uploads!!");
                }
            });
      } 
      //支持FF
      else if (document.implementation && document.implementation.createDocument) { 
        var xmlDoc; 
        xmlDoc = document.implementation.createDocument("", "", null); 
        xmlDoc.async = false; 
        xmlDoc.load(input.value); 
        var paramjson = xmlDoc.xml;
        //post file content
          $.ajax({
                type: "GET",
                async: false,
                url: "http://"+localip+":4000/do/programs/uploads",
                data: JSON.parse(paramjson),
                dataType: "json",
                success: function(data){
                    if(data.sts == 8){
                        window.location = "/login.esp";
                    }else if(data.sts == 5){
                        alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                        return false;
                    }
                    
                },
                error : function(err) {
                    alert("AJAX ERROR---uploads!!");
                }
            });
      } else { 
        alert('error'); 
      } 
    }

    $('#sendfile').on('click', function(){
        upload($('#file1')[0]);
    });
}

function gbl_download() {
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    
    function writeFile(data) {
        var BB = this.Blob;
        saveAs(
              new BB(
                  [data]
                , {type: "text/plain;charset=" + document.characterSet}
            )
            , "test.txt"
        );
      }
    //get back up data
    $.ajax({
          type: "GET",
          async: false,
          url: "http://"+localip+":4000/do/programs/downloads",
          dataType: "json",
          success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                    return false;
                }
                alert(JSON.stringify(data));
                writeFile(JSON.stringify(data));
 
                
                /*var fileWriter = new FileWriter();
                fileWriter.onwriteend = function() {
                    if (fileWriter.length === 0) {
                        //fileWriter has been reset, write file
                        fileWriter.write(blob);
                    } else {
                        //file has been overwritten with blob
                        //use callback or resolve promise
                    }
                };
                fileWriter.truncate(0);*/
          },
          error : function(err) {
              alert("AJAX ERROR---downloads!!");
          }
      });
}








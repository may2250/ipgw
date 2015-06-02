	//var dataSet = [];

    function alarm_output(flag){
		if(flag == 1){
			//告警日志
			//TODO
			//获取告警信息

            dataSet.length = 0;
			$('.main-content').empty();
			$('.main-content').append('<table cellpadding="0" cellspacing="0" border="0" class="cell-border compact hover" id="alarm"></table>');
			
			$('#alarm').dataTable( {
				"data": dataSet,
				"order": [[ 0, "desc" ]],
				"paging":   true,
				"info":     false,
                "bLengthChange": false,					//用户不可改变每页显示数量
                "iDisplayLength": 10,					//每页显示8条数据
                "searching":   true,
				"scrollY":  "368px",
				"scrollCollapse": true,
				"columns": [
					{ "title": "序号", "width":"10%" },
					{ "title": "等级" , "width":"10%"},
					{ "title": "用户" , "width":"10%"},
					{ "title": "详细信息", "class": "center", "width":"20%" },
					{ "title": "时间", "class": "center" }
				],
                "oLanguage": {							//汉化
                    "sLengthMenu": "每页显示 _MENU_ 条记录",
                    "sZeroRecords": "没有检索到数据",
                    "sInfo": "当前数据为从第 _START_ 到第 _END_ 条数据；总共有 _TOTAL_ 条记录",
                    "sInfoEmtpy": "没有数据",
                    "sProcessing": "正在加载数据...",
                    "sSearch": "搜索",
                    "oPaginate": {
                        "sFirst": "首页",
                        "sPrevious": "前页",
                        "sNext": "后页",
                        "sLast": "尾页"
                    }
                }
			});    
		}else if(flag == 2){
			//日志信息
            dataSet.length = 0;
            $.ajax({
                type: "GET",
                async:false,
                url: "http://"+globalObj.localip+":4000/do/globalopt/getoptlogs",
                // data: {ip:"192.168.1.134", inch:2},
                dataType: "json",
                success: function(data){
                    if(data.sts == 9){
                        window.location = "/login.esp";
                        return;
                    }
                    $.each(data, function(key, itemv) {
                        var logtime = new Date(parseInt(itemv.logtime) * 1000);
                        var datetime = logtime.toLocaleString().replace(/年|月/g, "-").replace(/日/g, " ");
                        var item = [itemv.id,itemv.user, itemv.desc, datetime];
                        dataSet[dataSet.length] = item;
                    });

                },
                error : function(err) {

                }
            });
			
			$('.main-content').empty();
			$('.main-content').append('<table cellpadding="0" cellspacing="0" border="0" class="cell-border compact hover" id="optlog"></table>');
			
			$('#optlog').dataTable( {
				"data": dataSet,
				"order": [[ 0, "desc" ]],
				"paging":   true,
				"info":     false,
                "bLengthChange": false,					//用户不可改变每页显示数量
                "iDisplayLength": 10,					//每页显示8条数据
				"searching":   true,
				"scrollY":  "368px",
				"scrollCollapse": true,
                "columns": [
					{ "title": "序号", "width":"10%" },
					{ "title": "用户" , "width":"10%"},
					{ "title": "详细信息" , "width":"20%"},
					{ "title": "时间", "class": "center" }
				],
                "oLanguage": {							//汉化
                    "sLengthMenu": "每页显示 _MENU_ 条记录",
                    "sZeroRecords": "没有检索到数据",
                    "sInfo": "当前数据为从第 _START_ 到第 _END_ 条数据；总共有 _TOTAL_ 条记录",
                    "sInfoEmtpy": "没有数据",
                    "sProcessing": "正在加载数据...",
                    "sSearch": "搜索",
                    "oPaginate": {
                        "sFirst": "首页",
                        "sPrevious": "前页",
                        "sNext": "后页",
                        "sLast": "尾页"
                    }
                }
			});    
		}
		
	}

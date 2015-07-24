var globalObj = {
    _outtable: null,
    _devtree: null,
    _sync: false,
    _nv: localStorage.getItem("language"),
    timerID: undefined
};

var channel_root = [
    {"title": globalObj._nv == "zh-CN"?"输入通道":"INPUT-CH", folder: true, key: "id1.0", expanded: true, "expanded": true, "icon": "img/book.ico"}
];

var StreamData = [];


var dig_notification = $( "#progress-notification" ).dialog({
    autoOpen: false,
    modal: true,
    width: 300
});

function getprgs(flag){
    $('.notification-tips')[0].textContent = globalObj._nv == "zh-CN"?"正在获取节目...":"Reading programes...";
    $( "#progress-notification").show();
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/getPrgs?flag="+flag,
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{
                var devlisttree = $("#devlist").fancytree("getTree");
                devlisttree.reload();
                var node = devlisttree.getNodeByKey("id1.0");
                res = JSON.stringify(res).replace('\\','');
                var treeData = JSON.parse(res);
                node.addChildren(treeData);
                ipread(1);
                iptvread();
                outprgList();
            }
        },
        error : function(err) {
            alert("AJAX ERROR---getPrgs!!");
        }
    });
}

function ipread(flag){
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/ipRead",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{
                if(flag == 1){
                    $('.output_ttl').val(res.ttl);
                    $('.output_mode')[0].options[Number(res.dvbIptvMode)].selected = true;
                    $('.spts_ch').attr("disabled", true);
                }else if(flag == 2){
                    //发送源
                    $('.s_netInterfaceMode')[0].options[Number(res.netInterfaceMode)].selected = true;
                    $('.s_ip').val(res.srcip);
                    $('.s_port').val(Number(res.port));
                    $('.s_mac').val(res.mac);
                }
            }
        },
        error : function(err) {
            alert("AJAX ERROR---ipRead!!");
        }
    });
}

function iptvread(){
    $('.notification-tips')[0].textContent = globalObj._nv == "zh-CN"?"正在获取IPTV信息...":"Reading IPTV information...";
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/iptvRead",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{

            }
        },
        error : function(err) {
            alert("AJAX ERROR---iptvRead!!");
        }
    });
}

function outprgList(){
    $('.notification-tips')[0].textContent = globalObj._nv == "zh-CN"?"正在获取输出列表...":"Reading Output List...";
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/outprgList",
        dataType: "json",
        success: function(data){
            if(data.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(data.sts == 8){
                window.location = "/login.esp";
            }else{
                StreamData.length = 0;
                $('.output_cnt').val(data.prgcnt);
                $.each(data.children, function(key, itemv) {
                    var item = [itemv.index,itemv.modeStr, itemv.ipStr,itemv.port,itemv.macStr, itemv.nameStr];
                    StreamData[StreamData.length] = item;
                });
                //编辑节目对话框表
                if ( $.fn.dataTable.isDataTable( '#tbl_outtable' ) ) {
                    $('#tbl_outtable').dataTable().fnClearTable();
                    $('#tbl_outtable').dataTable().fnAddData(StreamData);
                }else{

                }
                var srow;
                $.each(data.children, function(key, itemv) {
                    if(itemv.Isoutprg){
                        srow = globalObj._outtable[0].rows[itemv.index];
                        $(srow).addClass('outprg');
                    }
                });

            }
        },
        error : function(err) {
            alert("AJAX ERROR---ipRead!!");
        }
    });
}

function setIpTvmode(mod){
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/setIpTvmode?mode="+mod,
        dataType: "json",
        success: function(data){
            if(data.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(data.sts == 8){
                window.location = "/login.esp";
            }else{

            }
        },
        error : function(err) {
            alert("AJAX ERROR---setIpTvmode!!");
        }
    });
}

function refreshIpInOutMode(){
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/refreshIpMode",
        dataType: "json",
        success: function(data){
            if(data.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(data.sts == 8){
                window.location = "/login.esp";
            }else{
                $('.d_InterfaceMode')[0].selectedIndex = data.mode;
            }
        },
        error : function(err) {
            alert("AJAX ERROR---refreshIpMode!!");
        }
    });
}

function createHomeUI(){
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<div class="field_head">'
                +'<fieldset>'
                    +'<legend class="i18n_SENDSETTING">Send Setting</legend>'
                    +'<table class="fieldset_tbl">'
                        +'<tr>'
                            +'<td>'
                                +'<label class="lb_mr i18n_OUTMODE">OUT-MODE</label>'
                                +'<select class="output_mode lb_mr">'
                                    +'<option value="0">MPTS</option>'
                                    +'<option value="1">SPTS</option>'
                                +'</select>'
                            +'</td>'
                            +'<td>'
                                +'<label class="lb_mr">TTL</label>'
                                +'<input class="output_ttl" type="text" />'
                                +'<label class="lb_mr">[0:255]</label>'
                            +'</td>'
                            +'<td>'
                                +'<label class="lb_mr i18n_OUTPRGTOTAL">TOTAL</label>'
                                +'<input class="output_cnt" type="text" />'
                            +'</td>'
                        +'</tr>'
                    +'</table>'
                +'</fieldset>'
            +'</div>'
            +'<div class="clearfix prg_content">'
                +'<div class="input_tree">'
                    +'<div class="input_spts">'
                        +'<lable class="lb_mr lb_ml i18n_SPTSCH">SPTS CH</lable>'
                        +'<select class="spts_ch"></select>'
                        +'<a href="javascript:void(0)" class="btn_css btn_spts i18n_BTNOK">OK</a>'
                    +'</div>'
                    +'<div class="tree_content">'
                        +'<div id="devlist" class="channel_input"></div>'
                    +'</div>'
                +'</div>'
                +'<div class="prg_detail">'
                    +'<table class="fieldset_tbl">'
                        +'<tr>'
                            +'<td><label class="lb_mr i18n_CHANNEL">CHANNEL</label></td>'
                            +'<td><input class="prg_ch lb_mr"></td>'
                            +'<td><a href="javascript:void(0)" class="btn_css btn_prg i18n_BTNOK">OK</a></td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr i18n_OUTWAY">Output Mode</label></td>'
                            +'<td><select class="prg_outmode">'
                                +'<option value="0" class="i18n_UNICASTUDP">Unicast-UDP</option><option value="1" class="i18n_MUTICASTUDP">Muticast-UDP</option>'
                            +'</select></td>'
                            +'<td</td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr i18n_DESTIPADDR">Dest IP</label></td>'
                            +'<td><input class="prg_destip" type="text" /></td>'
                            +'<td><label>(eg:192.168.1.103)</label></td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr i18n_DESTPORT">Dest Port</label></td>'
                            +'<td><input class="prg_destport" type="text" /></td>'
                            +'<td><label>(1~65535)</label></td>'
                        +'</tr>'
                        +'<tr>'
                            +'<td><label class="lb_mr i18n_DESTMAC">Dest MAC</label></td>'
                            +'<td><input class="prg_destmac" type="text" /></td>'
                            +'<td><label>(eg:00:11:22:33:44:55)</label></td>'
                        +'</tr>'
                    +'</table>'
                    +'<div id="out_table">'
                        +'<table cellpadding="0" cellspacing="0" border="0" class="cell-border compact hover" id="tbl_outtable"></table>'
                    +'</div>'
                +'</div>'
            +'</div>'
            +'<div class="tbn_div">'
                +'<button id="output-search" class="i18n_BTNSEARCH">Search</button>'
                +'<button id="output-read" class="i18n_BTNREAD">Read</button>'
                +'<button id="output-auto" class="i18n_BTNAUTOTRANS">Auto Mapping</button>'
                +'<button id="output-clear" class="i18n_BTNCLEAR">Clear</button>'
                +'<button id="output-write" class="i18n_BTNAPPLY">Apply</button>'
            +'</div>'
        +'</div>'
    );
    
    $.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_SENDSETTING').html($.i18n.prop('SENDSETTING'));
            $('.i18n_OUTMODE').html($.i18n.prop('OUTMODE'));
            $('.i18n_OUTPRGTOTAL').html($.i18n.prop('OUTPRGTOTAL'));
            $('.i18n_SPTSCH').html($.i18n.prop('SPTSCH'));
            $('.i18n_BTNOK')[0].textContent = $.i18n.prop('BTNOK');
            $('.i18n_BTNOK')[1].textContent = $.i18n.prop('BTNOK');
            $('.i18n_CHANNEL').html($.i18n.prop('CHANNEL'));            
            $('.i18n_OUTWAY').html($.i18n.prop('OUTWAY'));            
            $('.i18n_DESTIPADDR').html($.i18n.prop('DESTIPADDR'));
            $('.i18n_DESTPORT').html($.i18n.prop('DESTPORT'));
            $('.i18n_DESTMAC').html($.i18n.prop('DESTMAC'));
            $('.i18n_UNICASTUDP')[0].textContent = $.i18n.prop('UNICASTUDP');
            $('.i18n_MUTICASTUDP')[0].textContent = $.i18n.prop('MUTICASTUDP');            
            $('.i18n_BTNSEARCH')[0].textContent = $.i18n.prop('BTNSEARCH');
            $('.i18n_BTNREAD')[0].textContent = $.i18n.prop('BTNREAD');            
            $('.i18n_BTNAUTOTRANS')[0].textContent = $.i18n.prop('BTNAUTOTRANS');
            $('.i18n_BTNCLEAR')[0].textContent = $.i18n.prop('BTNCLEAR');            
            $('.i18n_BTNAPPLY')[0].textContent = $.i18n.prop('BTNAPPLY');
            
        }
    });

    $('.output_cnt').attr("disabled", true);
    $('.prg_ch').attr("disabled", true);
    $('.spts_ch').attr("disabled", true);
    $('.btn_spts').attr("disabled", true);

    $('.btn_spts').on("click", function(){
        var selectednode = $("#devlist").fancytree("getTree").getActiveNode();
        if(selectednode != null && selectednode.data.prgnum != undefined){
            var prgId = selectednode.data.prgnum;
            var outChnId = isNaN($(".spts_ch").val())?0:$(".spts_ch").val();
            var jsonstr = '{"inCh":1,"prgId":' + prgId + ',"outChnId":' + outChnId + '}';
            $.ajax({
                type: "GET",
                async: false,
                url: "http://"+localip+":4000/do/programs/outchnprg_output",
                data: JSON.parse(jsonstr),
                dataType: "json",
                success: function(data){
                    if(data.sts == 6){
                        alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error!");
                        return false;
                    }
                    outprgList();
                },
                error : function(err) {
                    alert("AJAX ERROR---outchnprg_output!!");
                }
            });
        }
    });

    $('.btn_prg').on("click", function(){
        var outchn = $('.prg_ch').val();
        var outMode = $('.prg_outmode').get(0).selectedIndex;
        var ipstr = $('.prg_destip').val();
        var port = $('.prg_destport').val();
        var macstr = $('.prg_destmac').val();

        if(isNaN(port)){
            alert(globalObj._nv == "zh-CN"?"非法的端口号.":"Illegal Port.");
        }else{
            if(parseInt(port)<1 || parseInt(port)>65535){
                alert(globalObj._nv == "zh-CN"?"非法的端口号.":"Illegal Port.");
            }
        }
        var regexp = /^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
        var valid = regexp.test(ipstr);
        if(!valid){
            alert(globalObj._nv == "zh-CN"?"无效的IP地址.":"Invalid IP.");
            return false;
        }
        if(macstr != "Auto"){
            regexp = /[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}/;
            valid = regexp.test(macstr);
            if(!valid){
                alert(globalObj._nv == "zh-CN"?"无效的MAC地址.":"Invalid MAC.");
                return false;
            }
        }
        var jsonstr = '{"outchn":"' + outchn + '","outMode":' + outMode + ',"macstr":"' + macstr + '","ipstr":"'
            + ipstr + '","port":' + port + '}';
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/outChnConfig",
            data: JSON.parse(jsonstr),
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                    return false;
                }
                if(data.outMode < 3){
                    $('.prg_outmode')[0].selectedIndex = 0;
                }else if(data.outMode == 3){
                    $('.prg_outmode')[0].selectedIndex = 1;
                }
                //$('.prg_ch').val(index + 1);
                $('.prg_destip').val(data.ipStr);
                $('.prg_destport').val(data.port);
                $('.prg_destmac').val(data.macStr);
                outprgList();
            },
            error : function(err) {
                alert("AJAX ERROR---outChnConfig!!");
            }
        });

    });

    $( "#output-search" ).button({
        icons: {
            primary: "ui-icon-search"
        }
    }).click(function( event ) {
        event.preventDefault();
        dig_notification.dialog( "open");
        getprgs(1);
        if($('.output_mode').get(0).selectedIndex == 1){
            $('.input_spts').css("display", "block");
            $('#output-auto').css("display", "");
            $('#output-clear').css("display", "");
        }else{
            $('.input_spts').css("display", "none");
            $('#output-auto').css("display", "none");
            $('#output-clear').css("display", "none");
        }
        dig_notification.dialog( "close" );
    });

    $( "#output-read" ).button({
        icons: {
            primary: "ui-icon-comment"
        }
    }).click(function( event ) {
        event.preventDefault();
        dig_notification.dialog( "open" );
        getprgs(2);
        if($('.output_mode').get(0).selectedIndex == 1){
            $('.input_spts').css("display", "block");
            $('#output-auto').css("display", "");
            $('#output-clear').css("display", "");
        }else{
            $('.input_spts').css("display", "none");
            $('#output-auto').css("display", "none");
            $('#output-clear').css("display", "none");
        }
        dig_notification.dialog( "close" );

    });

    $( "#output-auto" ).button({
        icons: {
            primary: "ui-icon-shuffle"
        }
    }).click(function( event ) {
        event.preventDefault();
        $("#devlist").fancytree("getTree").getRootNode().setActive();
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/prgMuxSptsMap",
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                    return false;
                }else if(data.sts == 1){
                    outprgList();
                }
            },
            error : function(err) {
                alert("AJAX ERROR---prgMuxSptsMap!!");
            }
        });
    });

    $( "#output-clear" ).button({
        icons: {
            primary: "ui-icon-trash"
        }
    }).click(function( event ) {
        event.preventDefault();
        $("#devlist").fancytree("getTree").getRootNode().setActive();
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/clearprgMux",
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                    return false;
                }else if(data.sts == 1){
                    outprgList();
                }
            },
            error : function(err) {
                alert("AJAX ERROR---clearprgMux!!");
            }
        });
    });

    $( "#output-write" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        $('.notification-tips')[0].textContent = globalObj._nv == "zh-CN"?"正在下发配置...":"Sending Config...";
        dig_notification.dialog( "open" );
        var ttl = $('.output_ttl').val();
        $.ajax({
            type: "GET",
            async: true,
            url: "http://"+localip+":4000/do/programs/muxprgwrite?ttl="+ttl +"&outmode="+$('.output_mode').get(0).selectedIndex ,
            dataType: "json",
            success: function(data){
                dig_notification.dialog( "close" );
                if(data.sts == 8){
                    window.location = "/login.esp";
                }else if(data.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                    return false;
                }else if(data.sts == 1){
                    //outprgList();
                }else if(data.sts == 2){
                    alert(globalObj._nv == "zh-CN"?"检测到错误的IP输出通道设置！":"Detected Error IP output channel setting!");
                }

            },
            error : function(err) {
                alert("AJAX ERROR---muxprgwrite!!");
            }
        });

    });

    //输入通道树
    globalObj._devtree = $("#devlist").fancytree({
        checkbox: false,
        selectMode: 1,
        minExpandLevel:2,
        source: channel_root,
        select: function(event, data) {

        },
        click: function(event, data) {
            if( $.ui.fancytree.getEventTargetType(event) === "title" ){
                data.node.toggleSelected();
            }
            var snode = data.node;
            var arr = snode.key.match(/\./g);
            if(arr.length == 2){
                var prgnum = snode.data.prgnum;
                $.ajax({
                    type: "GET",
                    async: false,
                    url: "http://"+localip+":4000/do/programs/tree_selctdprg?prgnum="+prgnum,
                    dataType: "json",
                    success: function(data){
                        if(data.sts == 8){
                            window.location = "/login.esp";
                        }
                        $('.spts_ch').attr("disabled", false);
                        $(".spts_ch").empty();
                        $.each(data.children, function(index, item){
                            var option = $("<option>").val(item.tag).text(item.tag);
                            $(".spts_ch").append(option);
                        });
                        $('.spts_ch')[0].selectedIndex = data.tag;

                    },
                    error : function(err) {
                        alert("AJAX ERROR---tree_selctdprg!!");
                    }
                });
                var srow = globalObj._outtable[0].rows[$('.spts_ch').val()];
                $('#tbl_outtable').DataTable().$('tr.selected').removeClass('selected');
                $(srow).addClass('selected');
                //$(srow).addClass('outprg');
                if(srow != undefined){
                    var index = $(srow)[0].cells[0].textContent-1;
                    $.ajax({
                        type: "GET",
                        async: false,
                        url: "http://"+localip+":4000/do/programs/tbl_selctdprg?index="+index,
                        dataType: "json",
                        success: function(data){
                            if(data.outMode < 3){
                                $('.prg_outmode')[0].selectedIndex = 0;
                            }else if(data.outMode == 3){
                                $('.prg_outmode')[0].selectedIndex = 1;
                            }
                            $('.prg_ch').val(index + 1);
                            $('.prg_destip').val(data.ipStr);
                            $('.prg_destport').val(data.port);
                            $('.prg_destmac').val(data.macStr);

                        },
                        error : function(err) {
                            alert("AJAX ERROR---tbl_selctdprg!!");
                        }
                    });
                }
            }
        }
    });

    //右侧table
    globalObj._outtable = $('#tbl_outtable').dataTable( {
        "data": StreamData,
        "order": [[ 0, "asc" ]],
        "paging":   false,
        "info":     false,
        "searching":   false,
        "width": 270,
        "scrollY": 265,
        "bAutoWidth": false,
        "columns": [
            { "title": globalObj._nv == "zh-CN"?"通道":"CH"},
            { "title": globalObj._nv == "zh-CN"?"输出方式":"OUT-MODE"},
            { "title": "IP"},
            { "title": globalObj._nv == "zh-CN"?"端口号":"PORT"},
            { "title": "MAC" },
            { "title": globalObj._nv == "zh-CN"?"节目名称":"NAME" }
        ]
    });

    $('#tbl_outtable tbody').on( 'click', 'tr', function () {
        $('#tbl_outtable').DataTable().$('tr.selected').removeClass('selected');
        $(this).addClass('selected');
        var index = $(this)[0].cells[0].textContent-1;
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/tbl_selctdprg?index="+index,
            dataType: "json",
            success: function(data){
                if(data.sts == 8){
                    window.location = "/login.esp";
                }
                if(data.outMode < 3){
                    $('.prg_outmode')[0].selectedIndex = 0;
                }else if(data.outMode == 3){
                    $('.prg_outmode')[0].selectedIndex = 1;
                }
                $('.prg_ch').val(index + 1);
                $('.prg_destip').val(data.ipStr);
                $('.prg_destport').val(data.port);
                $('.prg_destmac').val(data.macStr);

            },
            error : function(err) {
                alert("AJAX ERROR---tbl_selctdprg!!");
            }
        });
        if($(this)[0].cells[4].textContent == "Auto"){
            $('.prg_destmac').attr("disabled", true);
        }else{
            $('.prg_destmac').attr("disabled", false);
        }
    } );

    $('.output_mode').on('change', function(){
        var spstindex = $('.output_mode')[0].selectedIndex;
        setIpTvmode(spstindex);
        if(spstindex){
            $('.input_spts').css("display", "block");
            $('#output-auto').css("display", "");
            $('#output-clear').css("display", "");
        }else{
            $('.input_spts').css("display", "none");
            $('#output-auto').css("display", "none");
            $('#output-clear').css("display", "none");
        }
        outprgList();
    });
}

function readipIN(){
    var flag = 0;
    if($('.chkb_valid')[0].checked == true){
        flag = 1;
    }
    $.ajax({
        type: "GET",
        async: false,
        url: "http://"+localip+":4000/do/programs/readipIN?flag="+ flag,
        dataType: "json",
        success: function(data){
            if(data.sts == 8){
                window.location = "/login.esp";
            }
            $('.tb_bitrate').val();
            $('.cb_net')[0].selectedIndex = data.unicastMulticast - 1;
            $('.tb_srcip').val(data.srcIp);
            $('.tb_ip').val(data.ip);
            $('.tb_mac').val(data.mac);
            $('.tb_port').val(data.port);
            $('.cb_streamType')[0].selectedIndex = data.inStreamType;
            if(data.valid){
                $('.chkb_valid')[0].checked = true;
            }else{
                $('.chkb_valid')[0].checked = false;
            }

        },
        error : function(err) {
            alert("AJAX ERROR---readipIN!!");
        }
    });
}

function readipinsts(){
    var flag = 0;
    if($('.chkb_valid')[0].checked == true){
        flag = 1;
    }
    $.ajax({
        type: "GET",
        async: true,
        url: "http://"+localip+":4000/do/programs/readipinsts?flag="+ flag,
        dataType: "json",
        success: function(data){
            if(data.sts == 8){
                window.location = "/login.esp";
            }else if(data.sts == 6){
                if(globalObj.timerID != undefined){
                    clearInterval(globalObj.timerID);
                }
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else{
                if(data.lockStatu == 0){
                    $('.panel_lock')[0].src = "../img/circle16_error.ico";
                }else if(data.lockStatu == 1){
                    $('.panel_lock')[0].src = "../img/circle16_green.ico";
                }else{
                    $('.panel_lock')[0].src = "../img/circle16_error.ico";
                }
                if (data.ipMode == 1){
                    $('.tb_ipNet').val("10/100 M");
                } else if (data.ipMode == 2){
                    $('.tb_ipNet').val("1000 M");
                } else if (data.ipMode == 3){
                    $('.tb_ipNet').val("10 M");
                } else if (data.ipMode == 4){
                    $('.tb_ipNet').val("100 M");
                }else{
                    $('.tb_ipNet').val("----");
                }
                $('.tb_percent').val(data.bufUsed.toString() + "%");
                $('.tb_bitrate').val(data.bitrate / 1000000);
            }

        },
        error : function(err) {
            alert("AJAX ERROR---readipinsts!!");
        }
    });
}

function createIPINUI(){
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<div class="field_head">'
                +'<fieldset>'
                +'<legend class="i18n_IPINPUT">IP-IN</legend>'
                +'<table class="fieldset_tbl">'
                    +'<tr>'
                        +'<td>'
                            +'<label class="lb_mr i18n_INLOCK">IN-LOCKED</label>'
                        +'</td>'
                        +'<td>'
                            +'<img class="lb_mr panel_lock" src="../img/circle16_error.ico"></label>'
                            +'<input class="tb_ipNet lb_ml1" type="text" disabled />'
                            +'<input class="tb_percent lb_ml1" type="text" disabled />'
                        +'</td>'
                        +'<td>'
                            +'<label class="lb_mr i18n_INRATE">Input Rate</label>'
                        +'</td>'
                        +'<td>'
                            +'<input class="tb_bitrate" type="text" disabled />'
                            +'<label>Mbps</label>'
                        +'</td>'
                    +'</tr>'
                    +'<tr>'
                        +'<td></td>'
                        +'<td>'
                            +'<input class="chkb_valid" name="chkb" type="checkbox" /><label class="i18n_ACTIVE">Active</label>'
                        +'</td>'
                        +'<td>'
                            +'<label class="lb_mr i18n_NETMODE">Net-Mode</label>'
                        +'</td>'
                        +'<td>'
                            +'<select class="cb_net">'
                                +'<option value="0">Unicast</option><option value="1">Multicast</option>'
                            +'</select>'
                        +'</td>'
                    +'</tr>'
                    +'<tr>'
                        +'<td>'
                            +'<label class="lb_mr i18n_SRCIP">Source IP</label>'
                        +'</td>'
                        +'<td>'
                            +'<input class="tb_srcip" type="text" style="width:120px" />'
                        +'</td>'
                        +'<td>'
                            +'<label class="lb_mr i18n_DEVIP">Device IP</label>'
                        +'</td>'
                        +'<td>'
                            +'<input class="tb_ip" type="text" style="width:120px"/>'
                        +'</td>'
                    +'</tr>'
                    +'<tr>'
                        +'<td>'
                            +'<label class="lb_mr i18n_RECEIVEPORT">Receive Port</label>'
                        +'</td>'
                        +'<td>'
                            +'<input class="tb_port" type="text" />'
                        +'</td>'
                        +'<td>'
                            +'<label class="lb_mr i18n_DEVMAC">Device MAC</label>'
                        +'</td>'
                        +'<td>'
                            +'<input class="tb_mac" type="text" style="width:120px" />'
                        +'</td>'
                    +'</tr>'
                    +'<tr>'
                        +'<td>'
                            +'<label class="lb_mr i18n_INSTREAMTYPE">In-StreamType</label>'
                        +'</td>'
                        +'<td>'
                            +'<select class="cb_streamType" style="width:100px">'
                                +'<option value="0" class="i18n_BUSINESSSTREAM">Business Stream</option><option value="1" class="i18n_AVSTREAM">AV Stream</option>'
                            +'</select>'
                        +'</td>'
                        +'<td>'
                        +'</td>'
                        +'<td>'
                        +'</td>'
                    +'</tr>'
                +'</table>'
                +'</fieldset>'
            +'</div>'
            +'<div class="tbn_div">'
                +'<button id="btn_ipinRead" class="i18n_BTNREAD">Read</button>'
                +'<button id="btn_ipinApply" class="i18n_BTNAPPLY">Apply</button>'
            +'</div>'
        +'</div>'
    );
    $.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_IPINPUT').html($.i18n.prop('IPINPUT'));
            $('.i18n_INLOCK').html($.i18n.prop('INLOCK'));
            $('.i18n_INRATE').html($.i18n.prop('INRATE'));            
            $('.i18n_ACTIVE').html($.i18n.prop('ACTIVE'));            
            $('.i18n_NETMODE').html($.i18n.prop('NETMODE'));            
            $('.i18n_SRCIP').html($.i18n.prop('SRCIP'));            
            $('.i18n_DEVIP').html($.i18n.prop('DEVIP'));            
            $('.i18n_RECEIVEPORT').html($.i18n.prop('RECEIVEPORT'));            
            $('.i18n_DEVMAC').html($.i18n.prop('DEVMAC'));            
            $('.i18n_INSTREAMTYPE').html($.i18n.prop('INSTREAMTYPE'));
            $('.i18n_BUSINESSSTREAM')[0].textContent = $.i18n.prop('BUSINESSSTREAM');            
            $('.i18n_AVSTREAM')[0].textContent = $.i18n.prop('AVSTREAM');
            $('.i18n_BTNREAD')[0].textContent = $.i18n.prop('BTNREAD');             
            $('.i18n_BTNAPPLY')[0].textContent = $.i18n.prop('BTNAPPLY');            
        }
    });
    readipIN();
    //创建定时器定时获取输出比特率
    globalObj.timerID = setInterval(readipinsts, 2000);
    $( "#btn_ipinRead" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        readipIN();
    });

    $( "#btn_ipinApply" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        var chk = $('.chkb_valid')[0].checked == true?1:0;
        var netMode = $('.cb_net').get(0).selectedIndex + 1;
        var ipstr = $('.tb_srcip').val();
        var desip = $('.tb_ip').val();
        var port = $('.tb_port').val();
        var macstr = $('.tb_mac').val();
        var streamType = $('.cb_streamType').get(0).selectedIndex;
        if(isNaN(port)){
            alert(globalObj._nv == "zh-CN"?"非法的端口号.":"Illegal Port.");
        }else{
            if(parseInt(port)<1 || parseInt(port)>65535){
                alert(globalObj._nv == "zh-CN"?"非法的端口号.":"Illegal Port.");
            }
        }
        var regexp = /^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
        var valid = regexp.test(ipstr) && regexp.test(desip);
        if(!valid){
            alert(globalObj._nv == "zh-CN"?"无效的IP地址.":"Invalid IP.");
            return false;
        }
        if(macstr != "Auto"){
            regexp = /[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}/;
            valid = regexp.test(macstr);
            if(!valid){
                alert(globalObj._nv == "zh-CN"?"无效的MAC地址.":"Invalid MAC.");
                return false;
            }
        }
        var jsonstr = '{"chk":"' + chk + '","netMode":' + netMode + ',"ipstr":"' + ipstr + '","desip":"'
            + desip + '","macstr":"' + macstr + '","port":' + port + ',"streamType":' + streamType + '}';
        $.ajax({
            type: "GET",
            async: true,
            url: "http://"+localip+":4000/do/programs/ipinApply",
            data: JSON.parse(jsonstr),
            dataType: "json",
            success: function(res){
                if(res.sts == 6){
                    alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
                }else if(res.sts == 8){
                    window.location = "/login.esp";
                }else{

                }
            },
            error : function(err) {
                alert("AJAX ERROR---readinputsts!!");
            }
        });
    });

}

function readinputsts(){
    $.ajax({
        type: "GET",
        async: true,
        url: "http://"+localip+":4000/do/programs/readinputsts",
        dataType: "json",
        success: function(res){
            if(res.sts == 6){
                alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
            }else if(res.sts == 8){
                window.location = "/login.esp";
            }else{
                $('.s_inrate').val(res.bitrate/1000000);
                if(res.lockStatus){
                    $('.s_inlock')[0].src = "../img/circle16_green.ico";
                }else{
                    $('.s_inlock')[0].src = "../img/circle16_error.ico";
                }
            }
        },
        error : function(err) {
            alert("AJAX ERROR---readinputsts!!");
        }
    });
}

function createSendSrcUI(){
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
            +'<fieldset>'
                +'<legend class="i18n_SENDSRC">Sender Source</legend>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr i18n_NETINTERFACEMODE">Net-Interface</label>'
                    +'<select class="s_netInterfaceMode lb_mr"><option value="0">10M</option>'
                        +'<option value="1">100M</option><option value="2">1000M</option>'
                        +'<option value="3">------</option>'
                    +'</select>'
                    +'<label class="lb_mr i18n_INRATE">Input Rate</label>'
                    +'<input class="s_inrate lb_mr" type="text" />Mbps'
                +'</div>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr i18n_SOURCEIP">Source IP</label>'
                    +'<input class="s_ip lb_mr" pattern="^(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(\\.(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3}$" type="text" />'
                    +'<label class="lb_mr">eg(192.168.1.103)</label>'
                +'</div>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr i18n_SOURCEPORT">Source Port</label>'
                    +'<input class="s_port lb_mr" type="text" />'
                    +'<label class="lb_mr">[0~65535]</label>'
                    +'<label class="lb_mr i18n_INLOCK">IN-LOCKED</label>'
                    +'<img src="" class="s_inlock lb_mr" />'
                +'</div>'
                +'<div class="sendsrcdiv">'
                    +'<label class="lb_mr i18n_SOURCEMAC">Source MAC</label>'
                    +'<input class="s_mac lb_mr" pattern="([0-9A-Fa-f]{2}-){5}[0-9A-Fa-f]{2})" type="text" />'
                    +'<label class="lb_mr i18n_16OX">HEX Value</label>'
                    +'<label class="lb_mr">eg(00:11:22:33:44:55)</label>'
                +'</div>'
            +'</fieldset>'
        +'</div>'

        +'<div class="tbn_div">'
            +'<button id="src-read" class="i18n_BTNREAD">Read</button>'
            +'<button id="src-write" class="i18n_BTNAPPLY">Apply</button>'
        +'</div>'
    );
    $.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_SENDSRC').html($.i18n.prop('SENDSRC'));
            $('.i18n_NETINTERFACEMODE').html($.i18n.prop('NETINTERFACEMODE'));            
            $('.i18n_INRATE').html($.i18n.prop('INRATE'));            
            $('.i18n_SOURCEIP').html($.i18n.prop('SOURCEIP'));            
            $('.i18n_SOURCEPORT').html($.i18n.prop('SOURCEPORT'));            
            $('.i18n_INLOCK').html($.i18n.prop('INLOCK'));            
            $('.i18n_SOURCEMAC').html($.i18n.prop('SOURCEMAC'));            
            $('.i18n_16OX').html($.i18n.prop('16OX'));           
            $('.i18n_BTNREAD')[0].textContent = $.i18n.prop('BTNREAD');             
            $('.i18n_BTNAPPLY')[0].textContent = $.i18n.prop('BTNAPPLY');            
        }
    });

    $('.s_inrate').attr("disabled", true);
    $('.s_netInterfaceMode').attr("disabled", true);

    ipread(2);
    //创建定时器定时获取输出比特率
    globalObj.timerID = setInterval(readinputsts,2000);

    $( "#src-read" ).button({
        icons: {
            primary: "ui-icon-comment"
        }
    }).click(function( event ) {
        event.preventDefault();
        ipread(2);
    });

    $( "#src-write" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        if(isNaN($('.s_port').val())){
            alert(globalObj._nv == "zh-CN"?"非法的端口号.":"Illegal Port.");
        }else{
            if(parseInt($('.s_port').val())>65535 || parseInt($('.s_port').val()<0)){
                alert(globalObj._nv == "zh-CN"?"端口号溢出.":"Port Overflow.");
                return false;
            }
        }
        var regexp = /^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/;
        var valid = regexp.test($('.s_ip').val());
        if(!valid){
            alert(globalObj._nv == "zh-CN"?"无效的IP地址.":"Invalid IP.");
            return false;
        }

        regexp = /[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}:[A-Fa-f0-9]{2}/;
        var valid = regexp.test($('.s_mac').val());
        if(!valid){
            alert(globalObj._nv == "zh-CN"?"无效的MAC地址.":"Invalid MAC.");
            return false;
        }

        var jsonstr = '{"ip":"' + $('.s_ip').val() + '","port":' + $('.s_port').val() + ',"mac":"' + $('.s_mac').val() + '"}';
        $.ajax({
            type: "GET",
            async: false,
            url: "http://"+localip+":4000/do/programs/ParamsWriteAll",
            data: JSON.parse(jsonstr),
            dataType: "json",
            success: function(res){
                if(res.sts == 6){
                    alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
                }else if(res.sts == 8){
                    window.location = "/login.esp";
                }else if(res.sts == 5){
                    alert(globalObj._nv == "zh-CN"?"该用户权限不足.":"Permission Denied!");
                }else{
                    alert(globalObj._nv == "zh-CN"?"下发成功.":"Config Success!");
                }
            },
            error : function(err) {
                alert("AJAX ERROR---ParamsWriteAll!!");
            }
        });
    });
}

function createDevFuncUI(){
    if(globalObj.timerID != undefined){
        clearInterval(globalObj.timerID);
    }
    $('.main-content').empty();
    $('.main-content').append(
        '<div class="src_content">'
        +'<fieldset>'
        +'<legend class="i18n_DEVFUNC">DEVICE FUNCTION</legend>'
        +'<div class="sendsrcdiv">'
            +'<label class="lb_mr i18n_NETINTERFACESET">Net-Interface Setting</label>'
            +'<select class="d_InterfaceMode lb_mr" style="width:100px"><option value="0">OUT</option>'
                +'<option value="1">IN</option>'
             +'</select>'
        +'</div>'
        +'<div><label class="lb_ml i18n_NETINTERFACEALARM">Warn：Modify Net-Interface mode， the device will reboot！</label></div>'
        +'<div class="tbn_div">'
            +'<button id="devfunc-read" class="i18n_BTNREAD">Read</button>'
            +'<button id="devfunc-write" class="i18n_BTNAPPLY">Apply</button>'
        +'</div>'
    );
    $.i18n.properties({
        name : globalObj._nv, //资源文件名称
        path : '/i18n/', //资源文件路径
        mode : 'map', //用Map的方式使用资源文件中的值
        language : globalObj._nv,
        callback : function() {//加载成功后设置显示内容
            $('.i18n_DEVFUNC').html($.i18n.prop('DEVFUNC'));
            $('.i18n_NETINTERFACESET').html($.i18n.prop('NETINTERFACESET'));            
            $('.i18n_NETINTERFACEALARM').html($.i18n.prop('NETINTERFACEALARM'));              
            $('.i18n_BTNREAD')[0].textContent = $.i18n.prop('BTNREAD');             
            $('.i18n_BTNAPPLY')[0].textContent = $.i18n.prop('BTNAPPLY');            
        }
    });

    refreshIpInOutMode();

    $( "#devfunc-read" ).button({
        icons: {
            primary: "ui-icon-comment"
        }
    }).click(function( event ) {
        event.preventDefault();
        refreshIpInOutMode();
    });

    $( "#devfunc-write" ).button({
        icons: {
            primary: "ui-icon-pencil"
        }
    }).click(function( event ) {
        event.preventDefault();
        if((confirm( globalObj._nv == "zh-CN"?"确定要修改吗？ ":"Sure to modify?")==true)){
            var mode = $('.d_InterfaceMode').get(0).selectedIndex;
            $.ajax({
                type: "GET",
                async: false,
                url: "http://"+localip+":4000/do/programs/netapply?mode="+mode,
                dataType: "json",
                success: function(data){
                    if(data.sts == 6){
                        alert(globalObj._nv == "zh-CN"?"通讯错误":"Communication Error.");
                    }else if(data.sts == 8){
                        window.location = "/login.esp";
                    }else{

                    }
                },
                error : function(err) {
                    alert("AJAX ERROR---netapply!!");
                }
            });
        }

    });
}




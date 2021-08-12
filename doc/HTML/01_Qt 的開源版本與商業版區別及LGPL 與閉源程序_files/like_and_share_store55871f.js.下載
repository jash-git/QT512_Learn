var _extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var o=arguments[t];
for(var n in o)Object.prototype.hasOwnProperty.call(o,n)&&(e[n]=o[n]);
}
return e;
};
define("pages_new/common_share/video/player/plugins/auto_next/auto_next_store.js",["biz_wap/jsapi/log.js","pages/utils.js","common/comm_report.js","biz_wap/utils/jsmonitor_report.js"],function(e){
"use strict";
var t=e("biz_wap/jsapi/log.js"),o=e("pages/utils.js"),n=e("common/comm_report.js"),s=e("biz_wap/utils/jsmonitor_report.js");
return{
name:"auto-next-plugin",
namespaced:!0,
state:function(){
return{
autoNextStatus:0
};
},
getters:{
nextVideo:function(e,t,o){
var n=o.extRes;
if(n.related_tag_video&&n.related_tag_video.length)for(var s=0;s<n.related_tag_video.length;s++){
var a=n.related_tag_video[s];
if(1!==a.user_read_status)return{
source:1,
vid:a.vid,
url:a.url,
recInfo:a.rec_info,
title:a.title||"更多精彩视频",
cover:a.cover||"",
headImg:a.head_img_url||"",
bizNickName:a.srcDisplayName||""
};
}
return null;
},
report17149Data:function(e,t,n){
var s=n.cgiData,a=n.extRes;
return{
BizUserName:s.biz,
MsgId:1*s.mid,
Idx:1*s.idx,
EnterId:s.enterid,
VideoId:s.vid,
Scene:s.scene,
Subscene:1*s.subscene,
SessionIdStr:s.sessionid,
ChannelSessionId:s.channel_session_id,
ContinueId:s.continueid+"",
ReloadId:s.reloadid+"",
Device:s.devicetype,
ContinueSource:t.nextVideo&&t.nextVideo.source||0,
MoreVideosInfo:t.nextVideo&&o.getMoreVideoInfo(t.nextVideo.url,t.nextVideo.vid)||"",
VideoRecommendType:a.video_recommend_type||0,
MoreVideoSortId:a.more_video_sort_id||0,
MoreVideosSeq:s.continueseq,
MoreVideoRecInfo:t.nextVideo&&t.nextVideo.recInfo||""
};
}
},
mutations:{
setAutoNextStatus:function(e,t){
e.autoNextStatus=t.value;
}
},
actions:{
cancelAutoNext:function(e,o){
var n=e.commit,s=e.state,a=e.dispatch;
0===s.autoNextStatus?(n("setAutoNextStatus",{
value:4
}),console.log("[AutoNext Plugin] Cancel autonext for reason "+o+" before tips show"),
t.info("cancel autonext for reason "+o+" before tips show")):a("cancelAutoNextWhenTipsShowed",o);
},
resumeAutoNext:function(e){
var o=e.commit,n=e.state;
4===n.autoNextStatus&&(o("setAutoNextStatus",{
value:0
}),console.log("[AutoNext Plugin] Resume autonext"),t.info("resume autonext"));
},
cancelAutoNextWhenTipsShowed:function(e,o){
var n=e.dispatch,a=e.state;
if(1===a.autoNextStatus){
n("hideTips");
var i=function(){
s.setSum(221764,28,1),n("report17149",{
EventType:87,
ContinueBreakReason:o
});
};
3===o?setTimeout(i):i(),console.log("[AutoNext Plugin] Cancel autonext for reason "+o+" when tips showed"),
t.info("cancel autonext for reason "+o+" when tips showed");
}
},
showTips:function(e){
var t=e.dispatch,o=e.commit,n=e.state;
0===n.autoNextStatus&&(o("setAutoNextStatus",{
value:1
}),s.setSum(221764,25,1),t("report17149",{
EventType:86
}));
},
hideTips:function(e){
var t=e.commit,o=e.state;
1===o.autoNextStatus&&t("setAutoNextStatus",{
value:3
});
},
report17149:function(e,t){
var o=e.getters,s=_extends({},o.report17149Data,t);
n.report(17149,s);
}
}
};
});define("pages_new/common_share/video/player/plugins/mid_ad/mid_ad_store.js",[],function(){
"use strict";
return{
name:"mid-ad-plugin",
namespaced:!0,
state:function(){
return{
midAdStatus:0
};
},
mutations:{
setMidAdStatus:function(t,e){
t.midAdStatus=e.value;
}
}
};
});define("pages_new/common_share/video/player/plugins/popup/popup_store.js",[],function(){
"use strict";
function t(t){
var p=Math.floor(t),u=Math.ceil(t);
return t>p&&p+.5>t?p+.5:t>p+.5&&u>t?u:t;
}
return{
name:"popup-plugin",
namespaced:!0,
state:function(){
return{
currentPopupIdx:-1,
popupData:null
};
},
getters:{
currentPopup:function(t){
var p=t.popupData&&t.popupData[t.currentPopupIdx];
return p&&2!==p.status?p:null;
}
},
mutations:{
setCurrentPopupIdx:function(t,p){
t.currentPopupIdx=p.value;
},
setPopupStatus:function(t,p){
var u=p.index||t.currentPopupIdx,e=t.popupData&&t.popupData[u];
e&&(e.status=p.value);
},
setPopupData:function(p,u){
p.popupData=u.value.dots.map(function(p){
var u={},e={};
try{
u=JSON.parse(p.dot);
}catch(n){}
try{
e=JSON.parse(p.position);
}catch(n){}
return{
status:0,
info:u,
id:p.id,
type:p.type,
position:e,
startTime:t(1*p.begin_time),
endTime:t(1*p.end_time)
};
});
}
}
};
});define("pages_new/common_share/video/player/plugins/danmu/danmu_store.js",[],function(){
"use strict";
return{
name:"danmu-plugin",
namespaced:!0,
state:function(){
return{
inputStatus:0,
danmuInfo:null
};
},
mutations:{
setInputStatus:function(n,t){
n.inputStatus=t.value;
},
setDanmuInfo:function(n,t){
n.danmuInfo=t;
}
}
};
});define("pages_new/common_share/video/player/plugins/tail/tail_store.js",[],function(){
"use strict";
return{
name:"tail-plugin",
namespaced:!0,
state:function(){
return{
tailStatus:0
};
},
mutations:{
setTailStatus:function(t,a){
t.tailStatus=a.value;
}
},
actions:{
setLikeStatus:function(t,a){
var e=t.rootState,s=t.commit;
s("SET_PRAISE_STATUS",{
hasPraised:a.hasPraised
},{
root:!0
}),s("SET_PRAISE_NUM",{
praiseNum:e.extRes.appmsgstat.old_like_num+(a.hasPraised?1:-1)
},{
root:!0
});
}
}
};
});define("pages_new/modules/reward/reward_store.js",[],function(){
"use strict";
return{
name:"mp-reward",
namespaced:!0
};
});var _slicedToArray=function(){
function e(e,t){
var n=[],r=!0,m=!1,o=void 0;
try{
for(var a,i=e[Symbol.iterator]();!(r=(a=i.next()).done)&&(n.push(a.value),!t||n.length!==t);r=!0);
}catch(s){
m=!0,o=s;
}finally{
try{
!r&&i["return"]&&i["return"]();
}finally{
if(m)throw o;
}
}
return n;
}
return function(t,n){
if(Array.isArray(t))return t;
if(Symbol.iterator in Object(t))return e(t,n);
throw new TypeError("Invalid attempt to destructure non-iterable instance");
};
}(),_extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var n=arguments[t];
for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r]);
}
return e;
};
define("pages_new/modules/comment/comment_store.js",["pages_new/3rd/vue.js","common/keyboard.js","common/utils.js","biz_wap/utils/mmversion.js","biz_wap/utils/jsmonitor_report.js"],function(e){
"use strict";
var t=e("pages_new/3rd/vue.js"),n=e("common/keyboard.js"),r=e("common/utils.js"),m=e("biz_wap/utils/mmversion.js"),o=e("biz_wap/utils/jsmonitor_report.js"),a="http://mmbiz.qpic.cn/mmbiz/a5icZrUmbV8p5jb6RZ8aYfjfS2AVle8URwBt8QIu6XbGewB9wiaWYWkPwq4R7pfdsFibuLkic16UcxDSNYtB8HnC1Q/0";
return{
name:"mp-comment",
namespaced:!0,
state:function(){
return{
writeStatus:0,
myCommentData:null,
myCommentStatus:0,
commentData:null,
commentStatus:0,
commentVersion:function(){
return m.isWechat?m.isInMiniProgram?0:n.canUseKeyboard?2:(m.isIOS||m.isAndroid)&&(m.gtVersion("7.0.8")||r.isNativePage())?2:0:0;
}(),
offset:0,
replyFlag:0,
warningToast:"",
reportData:{
scene:0,
idkey:"",
moreList:27,
repeatList:25,
errList:18,
handleList:26,
addCommentErr:19,
errComment:18,
repeatContent:24,
repeatContentID:23
}
};
},
getters:{
tempKey:function(e,t,n){
return n.cgiData.tempkey||"";
},
commentId:function(e,t,n){
return n.cgiData.comment_id||"";
},
commentEnabled:function(e,t,n){
return n.extRes.comment_enabled||0;
},
commentCount:function(e,t,n){
return n.extRes.comment_count;
},
nickName:function(e,t,n){
return n.extRes.nick_name||"";
},
headImg:function(e,t,n){
return n.extRes.logo_url||a;
},
isFans:function(e,t,n){
return n.extRes.is_fans||0;
},
isFansDays:function(e,t,n){
return n.extRes.is_fans_days||0;
},
onlyFansCanComment:function(e,t,n){
return n.extRes.only_fans_can_comment||0;
},
onlyFansDaysCanComment:function(e,t,n){
return n.extRes.only_fans_days_can_comment||0;
},
canC2cReply:function(e,t,n){
return!!n.extRes.test_flag&&0!==(256&n.extRes.test_flag);
}
},
mutations:{
setCommentVersion:function(e,t){
e.commentVersion=t.value;
},
setWriteStatus:function(e,t){
e.writeStatus=t.status;
},
setMyCommentData:function(e,t){
e.myCommentData=t.data;
},
setMyCommentStatus:function(e,t){
e.myCommentStatus=t.status;
},
setCommentData:function(e,t){
e.commentData=t.data;
},
setCommentLike:function(e,t){
var n=t.type,r=void 0===n?"mine":n,m=t.commentIdx,o=t.replyIdx,a=t.likeStatus,i="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof m&&"undefined"==typeof o){
var s=i[m];
s&&s.like_status!==a&&(s.like_status=a,s.like_num+=a?1:-1);
}else if("number"==typeof m&&"number"==typeof o){
var s=i[m],u=s.reply_new.reply_list[o];
u&&u.reply_like_status!==a&&(u.reply_like_status=a,u.reply_like_num+=a?1:-1,s.reply_new=_extends({},s.reply_new));
}
},
setAnimationStatus:function(e,t){
var n=t.type,r=void 0===n?"mine":n,m=t.commentIdx,o=t.replyIdx,a="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof m&&"undefined"==typeof o){
var i=a[m];
i&&(i.needAnimation=!1);
}else if("number"==typeof m&&"number"==typeof o){
var i=a[m],s=i.reply_new.reply_list[o];
s&&(s.needAnimation=!1);
}
},
addComment:function(e,n){
var r=n.type,m=void 0===r?"mine":r,o=n.commentItem,a=n.commentIdx,i=n.replyItem,s=n.replyIdx,u="mine"===m?e.myCommentData.my_comment:e.commentData.elected_comment;
if("undefined"!=typeof o)u.unshift(o);else if("number"==typeof a&&"undefined"!=typeof i){
var c=u[a];
c&&(c.reply_new?("number"==typeof s?c.reply_new.reply_list.splice(s+1,0,i):c.reply_new.reply_list.unshift(i),
c.reply_new.reply_total_cnt++,c.reply_new=_extends({},c.reply_new)):t.set(c,"reply_new",{
reply_list:[i],
reply_total_cnt:1
}));
}
},
removeComment:function(e,t){
var n=t.type,r=void 0===n?"mine":n,m=t.commentIdx,o=t.replyIdx,a="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof m&&"undefined"==typeof o)a.splice(m,1);else if("number"==typeof m&&"number"==typeof o){
var i=a[m];
i&&(i.reply_new.reply_list.splice(o,1),i.reply_new.reply_total_cnt--,i.reply_new=_extends({},i.reply_new));
}
},
updateCommentReplyInfo:function(e,t){
var n=t.commentIdx,r=t.key,m=t.value;
if("number"==typeof n){
var o=e.commentData.elected_comment[n];
o&&o.reply_new&&r in o.reply_new&&(o.reply_new[r]=m,o.reply_new=_extends({},o.reply_new));
}
},
setCommentStatus:function(e,t){
e.commentStatus=t.status;
},
setOffset:function(e,t){
e.offset=t.value;
},
setReplyFlag:function(e,t){
e.replyFlag=t.flag;
},
setReportData:function(e,t){
e.reportData=t.data;
},
setWarningToast:function(e,t){
e.warningToast=t.content;
}
},
actions:{
myReport:function(e,t){
var n=e.state,r=_slicedToArray(t,2),m=r[0],a=r[1],i=void 0===a?"":a;
if("undefined"!=typeof m)if(n.reportData.idkey)o.setSum(n.reportData.idkey,m,1);else{
var s=new Image,u=Math.random();
s.src="/mp/jsreport?key="+m+"&content="+i+"&r="+u;
}
}
}
};
});define("pages_new/common_share/video/topic/topic_store.js",[],function(){
"use strict";
return{
name:"mp-topic",
namespaced:!0,
state:function(){
return{
reportStatus:[]
};
},
getters:{
list:function(t,e,n){
var r=n.cgiData.topics||[];
return r;
},
reportStatus:function(t){
return t.reportStatus;
},
hasDesc:function(t,e,n){
return!!n.cgiData.msg_desc;
},
canReward:function(t,e,n){
return n.cgiData.is_need_reward;
}
},
mutations:{
REPORT_ITEM:function(t,e){
t.reportStatus[e]=!0;
}
},
actions:{
reportItem:function(t,e){
t.commit("REPORT_ITEM",e);
}
}
};
});define("pages_new/common_share/video/like_and_share/like_and_share_store.js",["pages_new/common_share/video/like_and_share/actions.js","pages_new/common_share/video/like_and_share/mutations.js","biz_wap/jsapi/core.js","biz_wap/utils/mmversion.js","biz_wap/utils/device.js"],function(e){
"use strict";
var s=e("pages_new/common_share/video/like_and_share/actions.js"),a=e("pages_new/common_share/video/like_and_share/mutations.js"),t=e("biz_wap/jsapi/core.js"),i=e("biz_wap/utils/mmversion.js"),n=e("biz_wap/utils/device.js");
return{
name:"mp-like-and-share",
namespaced:!0,
getters:{
hasExtReqDone:function(e,s,a){
var i=a.extRes;
return i.appmsgstat&&t.invoke("handleHaokanAction",{
imgUrl:a.cgiData.round_head_img?a.cgiData.round_head_img:"",
link:a.cgiData.msg_link.html(!1),
desc:a.cgiData.msg_desc||"",
title:a.cgiData.msg_title,
action:"update_recommend_status",
permission:a.cgiData.is_temp_url||a.extRes.appmsgstat.show_like_gray||!a.extRes.appmsgstat.show_like||2!==a.cgiData.appmsg_like_type?0:1,
recommend:a.extRes.appmsgstat.liked?1:0
},function(){}),!!i.appmsgstat;
},
test:function(e,s,a){
return a.extRes;
},
collectShow:function o(e,s,a){
var o=!1;
return(i.isWechat&&(n.os.iphone&&i.getInner()>"17001000"||n.os.android&&i.getInner()>"27001300")||n.os.windows&&i.getInner()>="63010000")&&(o=!0),
o&&a.extRes.share_flag.show;
},
shareShow:function r(e,s,a){
var r=!1;
return n.os.pc?n.os.windows&&i.getInner()>="63010000"&&(r=!0):r=!0,r&&a.extRes.share_flag.show;
}
},
mutations:a,
actions:s
};
});
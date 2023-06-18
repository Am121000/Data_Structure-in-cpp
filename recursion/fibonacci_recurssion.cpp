<!DOCTYPE html>
<!-- saved from url=(0058)https://www.programiz.com/cpp-programming/online-compiler/ -->
<html><script src="./fibonacci_recurssion_files/f.txt"></script><script async="" src="./fibonacci_recurssion_files/apstag.js.download"></script><script type="text/javascript" async="" src="./fibonacci_recurssion_files/js"></script><script type="text/javascript" async="" src="./fibonacci_recurssion_files/analytics.js.download"></script><script async="" src="./fibonacci_recurssion_files/gtm.js.download"></script><script>
    window[Symbol.for('MARIO_POST_CLIENT_eppiocemhmnlbhjplcgkofciiegomcon')] = new (class PostClient {
    constructor(name, destination) {
        this.name = name;
        this.destination = destination;
        this.serverListeners = {};
        this.bgRequestsListeners = {};
        this.bgEventsListeners = {};
        window.addEventListener('message', (message) => {
            const data = message.data;
            const isNotForMe = !(data.destination && data.destination === this.name);
            const hasNotEventProp = !data.event;
            if (isNotForMe || hasNotEventProp) {
                return;
            }
            if (data.event === 'MARIO_POST_SERVER__BG_RESPONSE') {
                const response = data.args;
                if (this.hasBgRequestListener(response.requestId)) {
                    try {
                        this.bgRequestsListeners[response.requestId](response.response);
                    }
                    catch (e) {
                        console.log(e);
                    }
                    delete this.bgRequestsListeners[response.requestId];
                }
            }
            else if (data.event === 'MARIO_POST_SERVER__BG_EVENT') {
                const response = data.args;
                if (this.hasBgEventListener(response.event)) {
                    try {
                        this.bgEventsListeners[data.id](response.payload);
                    }
                    catch (e) {
                        console.log(e);
                    }
                }
            }
            else if (this.hasServerListener(data.event)) {
                try {
                    this.serverListeners[data.event](data.args);
                }
                catch (e) {
                    console.log(e);
                }
            }
            else {
                console.log(`event not handled: ${data.event}`);
            }
        });
    }
    emitToServer(event, args) {
        const id = this.generateUIID();
        const message = {
            args,
            destination: this.destination,
            event,
            id,
        };
        window.postMessage(message, location.origin);
        return id;
    }
    emitToBg(bgEventName, args) {
        const requestId = this.generateUIID();
        const request = { bgEventName, requestId, args };
        this.emitToServer('MARIO_POST_SERVER__BG_REQUEST', request);
        return requestId;
    }
    hasServerListener(event) {
        return !!this.serverListeners[event];
    }
    hasBgRequestListener(requestId) {
        return !!this.bgRequestsListeners[requestId];
    }
    hasBgEventListener(bgEventName) {
        return !!this.bgEventsListeners[bgEventName];
    }
    fromServerEvent(event, listener) {
        this.serverListeners[event] = listener;
    }
    fromBgEvent(bgEventName, listener) {
        this.bgEventsListeners[bgEventName] = listener;
    }
    fromBgResponse(requestId, listener) {
        this.bgRequestsListeners[requestId] = listener;
    }
    generateUIID() {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
            const r = Math.random() * 16 | 0, v = c === 'x' ? r : (r & 0x3 | 0x8);
            return v.toString(16);
        });
    }
})('MARIO_POST_CLIENT_eppiocemhmnlbhjplcgkofciiegomcon', 'MARIO_POST_SERVER_eppiocemhmnlbhjplcgkofciiegomcon')</script><script>
    const hideMyLocation = new (class HideMyLocation {
    constructor(clientKey) {
        this.clientKey = clientKey;
        this.watchIDs = {};
        this.client = window[Symbol.for(clientKey)];
        const getCurrentPosition = navigator.geolocation.getCurrentPosition;
        const watchPosition = navigator.geolocation.watchPosition;
        const clearWatch = navigator.geolocation.clearWatch;
        const self = this;
        navigator.geolocation.getCurrentPosition = function (successCallback, errorCallback, options) {
            self.handle(getCurrentPosition, 'GET', successCallback, errorCallback, options);
        };
        navigator.geolocation.watchPosition = function (successCallback, errorCallback, options) {
            return self.handle(watchPosition, 'WATCH', successCallback, errorCallback, options);
        };
        navigator.geolocation.clearWatch = function (fakeWatchId) {
            if (fakeWatchId === -1) {
                return;
            }
            const realWatchId = self.watchIDs[fakeWatchId];
            delete self.watchIDs[fakeWatchId];
            return clearWatch.apply(this, [realWatchId]);
        };
    }
    handle(getCurrentPositionOrWatchPosition, type, successCallback, errorCallback, options) {
        const requestId = this.client.emitToBg('HIDE_MY_LOCATION__GET_LOCATION');
        let fakeWatchId = this.getRandomInt(0, 100000);
        this.client.fromBgResponse(requestId, (response) => {
            if (response.enabled) {
                if (response.status === 'SUCCESS') {
                    const position = this.map(response);
                    successCallback(position);
                }
                else {
                    const error = this.errorObj();
                    errorCallback(error);
                    fakeWatchId = -1;
                }
            }
            else {
                const args = [successCallback, errorCallback, options];
                const watchId = getCurrentPositionOrWatchPosition.apply(navigator.geolocation, args);
                if (type === 'WATCH') {
                    this.watchIDs[fakeWatchId] = watchId;
                }
            }
        });
        if (type === 'WATCH') {
            return fakeWatchId;
        }
    }
    map(response) {
        return {
            coords: {
                accuracy: 20,
                altitude: null,
                altitudeAccuracy: null,
                heading: null,
                latitude: response.latitude,
                longitude: response.longitude,
                speed: null,
            },
            timestamp: Date.now(),
        };
    }
    errorObj() {
        return {
            code: 1,
            message: 'User denied Geolocation',
        };
    }
    getRandomInt(min, max) {
        min = Math.ceil(min);
        max = Math.floor(max);
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }
})('MARIO_POST_CLIENT_eppiocemhmnlbhjplcgkofciiegomcon')
  </script><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"><script type="text/javascript" async="" src="./fibonacci_recurssion_files/localstore.js.download"></script><style>    .error_widget_wrapper {        background: inherit;        color: inherit;        border:none    }    .error_widget {        border-top: solid 2px;        border-bottom: solid 2px;        margin: 5px 0;        padding: 10px 40px;        white-space: pre-wrap;    }    .error_widget.ace_error, .error_widget_arrow.ace_error{        border-color: #ff5a5a    }    .error_widget.ace_warning, .error_widget_arrow.ace_warning{        border-color: #F1D817    }    .error_widget.ace_info, .error_widget_arrow.ace_info{        border-color: #5a5a5a    }    .error_widget.ace_ok, .error_widget_arrow.ace_ok{        border-color: #5aaa5a    }    .error_widget_arrow {        position: absolute;        border: solid 5px;        border-top-color: transparent!important;        border-right-color: transparent!important;        border-left-color: transparent!important;        top: -5px;    }</style><style id="ace-tm">.ace-tm .ace_gutter {background: #f0f0f0;color: #333;}.ace-tm .ace_print-margin {width: 1px;background: #e8e8e8;}.ace-tm .ace_fold {background-color: #6B72E6;}.ace-tm {background-color: #FFFFFF;color: black;}.ace-tm .ace_cursor {color: black;}.ace-tm .ace_invisible {color: rgb(191, 191, 191);}.ace-tm .ace_storage,.ace-tm .ace_keyword {color: blue;}.ace-tm .ace_constant {color: rgb(197, 6, 11);}.ace-tm .ace_constant.ace_buildin {color: rgb(88, 72, 246);}.ace-tm .ace_constant.ace_language {color: rgb(88, 92, 246);}.ace-tm .ace_constant.ace_library {color: rgb(6, 150, 14);}.ace-tm .ace_invalid {background-color: rgba(255, 0, 0, 0.1);color: red;}.ace-tm .ace_support.ace_function {color: rgb(60, 76, 114);}.ace-tm .ace_support.ace_constant {color: rgb(6, 150, 14);}.ace-tm .ace_support.ace_type,.ace-tm .ace_support.ace_class {color: rgb(109, 121, 222);}.ace-tm .ace_keyword.ace_operator {color: rgb(104, 118, 135);}.ace-tm .ace_string {color: rgb(3, 106, 7);}.ace-tm .ace_comment {color: rgb(76, 136, 107);}.ace-tm .ace_comment.ace_doc {color: rgb(0, 102, 255);}.ace-tm .ace_comment.ace_doc.ace_tag {color: rgb(128, 159, 191);}.ace-tm .ace_constant.ace_numeric {color: rgb(0, 0, 205);}.ace-tm .ace_variable {color: rgb(49, 132, 149);}.ace-tm .ace_xml-pe {color: rgb(104, 104, 91);}.ace-tm .ace_entity.ace_name.ace_function {color: #0000A2;}.ace-tm .ace_heading {color: rgb(12, 7, 255);}.ace-tm .ace_list {color:rgb(185, 6, 144);}.ace-tm .ace_meta.ace_tag {color:rgb(0, 22, 142);}.ace-tm .ace_string.ace_regex {color: rgb(255, 0, 0)}.ace-tm .ace_marker-layer .ace_selection {background: rgb(181, 213, 255);}.ace-tm.ace_multiselect .ace_selection.ace_start {box-shadow: 0 0 3px 0px white;}.ace-tm .ace_marker-layer .ace_step {background: rgb(252, 255, 0);}.ace-tm .ace_marker-layer .ace_stack {background: rgb(164, 229, 101);}.ace-tm .ace_marker-layer .ace_bracket {margin: -1px 0 0 -1px;border: 1px solid rgb(192, 192, 192);}.ace-tm .ace_marker-layer .ace_active-line {background: rgba(0, 0, 0, 0.07);}.ace-tm .ace_gutter-active-line {background-color : #dcdcdc;}.ace-tm .ace_marker-layer .ace_selected-word {background: rgb(250, 250, 255);border: 1px solid rgb(200, 200, 250);}.ace-tm .ace_indent-guide {background: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAACCAYAAACZgbYnAAAAE0lEQVQImWP4////f4bLly//BwAmVgd1/w11/gAAAABJRU5ErkJggg==") right repeat-y;}
/*# sourceURL=ace/css/ace-tm */</style><style id="ace_editor.css">.ace_br1 {border-top-left-radius    : 3px;}.ace_br2 {border-top-right-radius   : 3px;}.ace_br3 {border-top-left-radius    : 3px; border-top-right-radius:    3px;}.ace_br4 {border-bottom-right-radius: 3px;}.ace_br5 {border-top-left-radius    : 3px; border-bottom-right-radius: 3px;}.ace_br6 {border-top-right-radius   : 3px; border-bottom-right-radius: 3px;}.ace_br7 {border-top-left-radius    : 3px; border-top-right-radius:    3px; border-bottom-right-radius: 3px;}.ace_br8 {border-bottom-left-radius : 3px;}.ace_br9 {border-top-left-radius    : 3px; border-bottom-left-radius:  3px;}.ace_br10{border-top-right-radius   : 3px; border-bottom-left-radius:  3px;}.ace_br11{border-top-left-radius    : 3px; border-top-right-radius:    3px; border-bottom-left-radius:  3px;}.ace_br12{border-bottom-right-radius: 3px; border-bottom-left-radius:  3px;}.ace_br13{border-top-left-radius    : 3px; border-bottom-right-radius: 3px; border-bottom-left-radius:  3px;}.ace_br14{border-top-right-radius   : 3px; border-bottom-right-radius: 3px; border-bottom-left-radius:  3px;}.ace_br15{border-top-left-radius    : 3px; border-top-right-radius:    3px; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px;}.ace_editor {position: relative;overflow: hidden;padding: 0;font: 12px/normal 'Monaco', 'Menlo', 'Ubuntu Mono', 'Consolas', 'source-code-pro', monospace;direction: ltr;text-align: left;-webkit-tap-highlight-color: rgba(0, 0, 0, 0);}.ace_scroller {position: absolute;overflow: hidden;top: 0;bottom: 0;background-color: inherit;-ms-user-select: none;-moz-user-select: none;-webkit-user-select: none;user-select: none;cursor: text;}.ace_content {position: absolute;box-sizing: border-box;min-width: 100%;contain: style size layout;font-variant-ligatures: no-common-ligatures;}.ace_dragging .ace_scroller:before{position: absolute;top: 0;left: 0;right: 0;bottom: 0;content: '';background: rgba(250, 250, 250, 0.01);z-index: 1000;}.ace_dragging.ace_dark .ace_scroller:before{background: rgba(0, 0, 0, 0.01);}.ace_selecting, .ace_selecting * {cursor: text !important;}.ace_gutter {position: absolute;overflow : hidden;width: auto;top: 0;bottom: 0;left: 0;cursor: default;z-index: 4;-ms-user-select: none;-moz-user-select: none;-webkit-user-select: none;user-select: none;contain: style size layout;}.ace_gutter-active-line {position: absolute;left: 0;right: 0;}.ace_scroller.ace_scroll-left {box-shadow: 17px 0 16px -16px rgba(0, 0, 0, 0.4) inset;}.ace_gutter-cell {position: absolute;top: 0;left: 0;right: 0;padding-left: 19px;padding-right: 6px;background-repeat: no-repeat;}.ace_gutter-cell.ace_error {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAMAAAAoLQ9TAAABOFBMVEX/////////QRswFAb/Ui4wFAYwFAYwFAaWGAfDRymzOSH/PxswFAb/SiUwFAYwFAbUPRvjQiDllog5HhHdRybsTi3/Tyv9Tir+Syj/UC3////XurebMBIwFAb/RSHbPx/gUzfdwL3kzMivKBAwFAbbvbnhPx66NhowFAYwFAaZJg8wFAaxKBDZurf/RB6mMxb/SCMwFAYwFAbxQB3+RB4wFAb/Qhy4Oh+4QifbNRcwFAYwFAYwFAb/QRzdNhgwFAYwFAbav7v/Uy7oaE68MBK5LxLewr/r2NXewLswFAaxJw4wFAbkPRy2PyYwFAaxKhLm1tMwFAazPiQwFAaUGAb/QBrfOx3bvrv/VC/maE4wFAbRPBq6MRO8Qynew8Dp2tjfwb0wFAbx6eju5+by6uns4uH9/f36+vr/GkHjAAAAYnRSTlMAGt+64rnWu/bo8eAA4InH3+DwoN7j4eLi4xP99Nfg4+b+/u9B/eDs1MD1mO7+4PHg2MXa347g7vDizMLN4eG+Pv7i5evs/v79yu7S3/DV7/498Yv24eH+4ufQ3Ozu/v7+y13sRqwAAADLSURBVHjaZc/XDsFgGIBhtDrshlitmk2IrbHFqL2pvXf/+78DPokj7+Fz9qpU/9UXJIlhmPaTaQ6QPaz0mm+5gwkgovcV6GZzd5JtCQwgsxoHOvJO15kleRLAnMgHFIESUEPmawB9ngmelTtipwwfASilxOLyiV5UVUyVAfbG0cCPHig+GBkzAENHS0AstVF6bacZIOzgLmxsHbt2OecNgJC83JERmePUYq8ARGkJx6XtFsdddBQgZE2nPR6CICZhawjA4Fb/chv+399kfR+MMMDGOQAAAABJRU5ErkJggg==");background-repeat: no-repeat;background-position: 2px center;}.ace_gutter-cell.ace_warning {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAMAAAAoLQ9TAAAAmVBMVEX///8AAAD///8AAAAAAABPSzb/5sAAAAB/blH/73z/ulkAAAAAAAD85pkAAAAAAAACAgP/vGz/rkDerGbGrV7/pkQICAf////e0IsAAAD/oED/qTvhrnUAAAD/yHD/njcAAADuv2r/nz//oTj/p064oGf/zHAAAAA9Nir/tFIAAAD/tlTiuWf/tkIAAACynXEAAAAAAAAtIRW7zBpBAAAAM3RSTlMAABR1m7RXO8Ln31Z36zT+neXe5OzooRDfn+TZ4p3h2hTf4t3k3ucyrN1K5+Xaks52Sfs9CXgrAAAAjklEQVR42o3PbQ+CIBQFYEwboPhSYgoYunIqqLn6/z8uYdH8Vmdnu9vz4WwXgN/xTPRD2+sgOcZjsge/whXZgUaYYvT8QnuJaUrjrHUQreGczuEafQCO/SJTufTbroWsPgsllVhq3wJEk2jUSzX3CUEDJC84707djRc5MTAQxoLgupWRwW6UB5fS++NV8AbOZgnsC7BpEAAAAABJRU5ErkJggg==");background-position: 2px center;}.ace_gutter-cell.ace_info {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAAAAAA6mKC9AAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAAJ0Uk5TAAB2k804AAAAPklEQVQY02NgIB68QuO3tiLznjAwpKTgNyDbMegwisCHZUETUZV0ZqOquBpXj2rtnpSJT1AEnnRmL2OgGgAAIKkRQap2htgAAAAASUVORK5CYII=");background-position: 2px center;}.ace_dark .ace_gutter-cell.ace_info {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQBAMAAADt3eJSAAAAJFBMVEUAAAChoaGAgIAqKiq+vr6tra1ZWVmUlJSbm5s8PDxubm56enrdgzg3AAAAAXRSTlMAQObYZgAAAClJREFUeNpjYMAPdsMYHegyJZFQBlsUlMFVCWUYKkAZMxZAGdxlDMQBAG+TBP4B6RyJAAAAAElFTkSuQmCC");}.ace_scrollbar {contain: strict;position: absolute;right: 0;bottom: 0;z-index: 6;}.ace_scrollbar-inner {position: absolute;cursor: text;left: 0;top: 0;}.ace_scrollbar-v{overflow-x: hidden;overflow-y: scroll;top: 0;}.ace_scrollbar-h {overflow-x: scroll;overflow-y: hidden;left: 0;}.ace_print-margin {position: absolute;height: 100%;}.ace_text-input {position: absolute;z-index: 0;width: 0.5em;height: 1em;opacity: 0;background: transparent;-moz-appearance: none;appearance: none;border: none;resize: none;outline: none;overflow: hidden;font: inherit;padding: 0 1px;margin: 0 -1px;contain: strict;-ms-user-select: text;-moz-user-select: text;-webkit-user-select: text;user-select: text;white-space: pre!important;}.ace_text-input.ace_composition {background: transparent;color: inherit;z-index: 1000;opacity: 1;}.ace_composition_placeholder { color: transparent }.ace_composition_marker { border-bottom: 1px solid;position: absolute;border-radius: 0;margin-top: 1px;}[ace_nocontext=true] {transform: none!important;filter: none!important;clip-path: none!important;mask : none!important;contain: none!important;perspective: none!important;mix-blend-mode: initial!important;z-index: auto;}.ace_layer {z-index: 1;position: absolute;overflow: hidden;word-wrap: normal;white-space: pre;height: 100%;width: 100%;box-sizing: border-box;pointer-events: none;}.ace_gutter-layer {position: relative;width: auto;text-align: right;pointer-events: auto;height: 1000000px;contain: style size layout;}.ace_text-layer {font: inherit !important;position: absolute;height: 1000000px;width: 1000000px;contain: style size layout;}.ace_text-layer > .ace_line, .ace_text-layer > .ace_line_group {contain: style size layout;position: absolute;top: 0;left: 0;right: 0;}.ace_hidpi .ace_text-layer,.ace_hidpi .ace_gutter-layer,.ace_hidpi .ace_content,.ace_hidpi .ace_gutter {contain: strict;will-change: transform;}.ace_hidpi .ace_text-layer > .ace_line, .ace_hidpi .ace_text-layer > .ace_line_group {contain: strict;}.ace_cjk {display: inline-block;text-align: center;}.ace_cursor-layer {z-index: 4;}.ace_cursor {z-index: 4;position: absolute;box-sizing: border-box;border-left: 2px solid;transform: translatez(0);}.ace_multiselect .ace_cursor {border-left-width: 1px;}.ace_slim-cursors .ace_cursor {border-left-width: 1px;}.ace_overwrite-cursors .ace_cursor {border-left-width: 0;border-bottom: 1px solid;}.ace_hidden-cursors .ace_cursor {opacity: 0.2;}.ace_hasPlaceholder .ace_hidden-cursors .ace_cursor {opacity: 0;}.ace_smooth-blinking .ace_cursor {transition: opacity 0.18s;}.ace_animate-blinking .ace_cursor {animation-duration: 1000ms;animation-timing-function: step-end;animation-name: blink-ace-animate;animation-iteration-count: infinite;}.ace_animate-blinking.ace_smooth-blinking .ace_cursor {animation-duration: 1000ms;animation-timing-function: ease-in-out;animation-name: blink-ace-animate-smooth;}@keyframes blink-ace-animate {from, to { opacity: 1; }60% { opacity: 0; }}@keyframes blink-ace-animate-smooth {from, to { opacity: 1; }45% { opacity: 1; }60% { opacity: 0; }85% { opacity: 0; }}.ace_marker-layer .ace_step, .ace_marker-layer .ace_stack {position: absolute;z-index: 3;}.ace_marker-layer .ace_selection {position: absolute;z-index: 5;}.ace_marker-layer .ace_bracket {position: absolute;z-index: 6;}.ace_marker-layer .ace_error_bracket {position: absolute;border-bottom: 1px solid #DE5555;border-radius: 0;}.ace_marker-layer .ace_active-line {position: absolute;z-index: 2;}.ace_marker-layer .ace_selected-word {position: absolute;z-index: 4;box-sizing: border-box;}.ace_line .ace_fold {box-sizing: border-box;display: inline-block;height: 11px;margin-top: -2px;vertical-align: middle;background-image:url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAAJCAYAAADU6McMAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAJpJREFUeNpi/P//PwOlgAXGYGRklAVSokD8GmjwY1wasKljQpYACtpCFeADcHVQfQyMQAwzwAZI3wJKvCLkfKBaMSClBlR7BOQikCFGQEErIH0VqkabiGCAqwUadAzZJRxQr/0gwiXIal8zQQPnNVTgJ1TdawL0T5gBIP1MUJNhBv2HKoQHHjqNrA4WO4zY0glyNKLT2KIfIMAAQsdgGiXvgnYAAAAASUVORK5CYII="),url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAA3CAYAAADNNiA5AAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAACJJREFUeNpi+P//fxgTAwPDBxDxD078RSX+YeEyDFMCIMAAI3INmXiwf2YAAAAASUVORK5CYII=");background-repeat: no-repeat, repeat-x;background-position: center center, top left;color: transparent;border: 1px solid black;border-radius: 2px;cursor: pointer;pointer-events: auto;}.ace_dark .ace_fold {}.ace_fold:hover{background-image:url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAAJCAYAAADU6McMAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAJpJREFUeNpi/P//PwOlgAXGYGRklAVSokD8GmjwY1wasKljQpYACtpCFeADcHVQfQyMQAwzwAZI3wJKvCLkfKBaMSClBlR7BOQikCFGQEErIH0VqkabiGCAqwUadAzZJRxQr/0gwiXIal8zQQPnNVTgJ1TdawL0T5gBIP1MUJNhBv2HKoQHHjqNrA4WO4zY0glyNKLT2KIfIMAAQsdgGiXvgnYAAAAASUVORK5CYII="),url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAA3CAYAAADNNiA5AAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAACBJREFUeNpi+P//fz4TAwPDZxDxD5X4i5fLMEwJgAADAEPVDbjNw87ZAAAAAElFTkSuQmCC");}.ace_tooltip {background-color: #FFF;background-image: linear-gradient(to bottom, transparent, rgba(0, 0, 0, 0.1));border: 1px solid gray;border-radius: 1px;box-shadow: 0 1px 2px rgba(0, 0, 0, 0.3);color: black;max-width: 100%;padding: 3px 4px;position: fixed;z-index: 999999;box-sizing: border-box;cursor: default;white-space: pre;word-wrap: break-word;line-height: normal;font-style: normal;font-weight: normal;letter-spacing: normal;pointer-events: none;}.ace_folding-enabled > .ace_gutter-cell {padding-right: 13px;}.ace_fold-widget {box-sizing: border-box;margin: 0 -12px 0 1px;display: none;width: 11px;vertical-align: top;background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAANElEQVR42mWKsQ0AMAzC8ixLlrzQjzmBiEjp0A6WwBCSPgKAXoLkqSot7nN3yMwR7pZ32NzpKkVoDBUxKAAAAABJRU5ErkJggg==");background-repeat: no-repeat;background-position: center;border-radius: 3px;border: 1px solid transparent;cursor: pointer;}.ace_folding-enabled .ace_fold-widget {display: inline-block;   }.ace_fold-widget.ace_end {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAANElEQVR42m3HwQkAMAhD0YzsRchFKI7sAikeWkrxwScEB0nh5e7KTPWimZki4tYfVbX+MNl4pyZXejUO1QAAAABJRU5ErkJggg==");}.ace_fold-widget.ace_closed {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAMAAAAGCAYAAAAG5SQMAAAAOUlEQVR42jXKwQkAMAgDwKwqKD4EwQ26sSOkVWjgIIHAzPiCgaqiqnJHZnKICBERHN194O5b9vbLuAVRL+l0YWnZAAAAAElFTkSuQmCCXA==");}.ace_fold-widget:hover {border: 1px solid rgba(0, 0, 0, 0.3);background-color: rgba(255, 255, 255, 0.2);box-shadow: 0 1px 1px rgba(255, 255, 255, 0.7);}.ace_fold-widget:active {border: 1px solid rgba(0, 0, 0, 0.4);background-color: rgba(0, 0, 0, 0.05);box-shadow: 0 1px 1px rgba(255, 255, 255, 0.8);}.ace_dark .ace_fold-widget {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHklEQVQIW2P4//8/AzoGEQ7oGCaLLAhWiSwB146BAQCSTPYocqT0AAAAAElFTkSuQmCC");}.ace_dark .ace_fold-widget.ace_end {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAH0lEQVQIW2P4//8/AxQ7wNjIAjDMgC4AxjCVKBirIAAF0kz2rlhxpAAAAABJRU5ErkJggg==");}.ace_dark .ace_fold-widget.ace_closed {background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAMAAAAFCAYAAACAcVaiAAAAHElEQVQIW2P4//+/AxAzgDADlOOAznHAKgPWAwARji8UIDTfQQAAAABJRU5ErkJggg==");}.ace_dark .ace_fold-widget:hover {box-shadow: 0 1px 1px rgba(255, 255, 255, 0.2);background-color: rgba(255, 255, 255, 0.1);}.ace_dark .ace_fold-widget:active {box-shadow: 0 1px 1px rgba(255, 255, 255, 0.2);}.ace_inline_button {border: 1px solid lightgray;display: inline-block;margin: -1px 8px;padding: 0 5px;pointer-events: auto;cursor: pointer;}.ace_inline_button:hover {border-color: gray;background: rgba(200,200,200,0.2);display: inline-block;pointer-events: auto;}.ace_fold-widget.ace_invalid {background-color: #FFB4B4;border-color: #DE5555;}.ace_fade-fold-widgets .ace_fold-widget {transition: opacity 0.4s ease 0.05s;opacity: 0;}.ace_fade-fold-widgets:hover .ace_fold-widget {transition: opacity 0.05s ease 0.05s;opacity:1;}.ace_underline {text-decoration: underline;}.ace_bold {font-weight: bold;}.ace_nobold .ace_bold {font-weight: normal;}.ace_italic {font-style: italic;}.ace_error-marker {background-color: rgba(255, 0, 0,0.2);position: absolute;z-index: 9;}.ace_highlight-marker {background-color: rgba(255, 255, 0,0.2);position: absolute;z-index: 8;}.ace_mobile-menu {position: absolute;line-height: 1.5;border-radius: 4px;-ms-user-select: none;-moz-user-select: none;-webkit-user-select: none;user-select: none;background: white;box-shadow: 1px 3px 2px grey;border: 1px solid #dcdcdc;color: black;}.ace_dark > .ace_mobile-menu {background: #333;color: #ccc;box-shadow: 1px 3px 2px grey;border: 1px solid #444;}.ace_mobile-button {padding: 2px;cursor: pointer;overflow: hidden;}.ace_mobile-button:hover {background-color: #eee;opacity:1;}.ace_mobile-button:active {background-color: #ddd;}.ace_placeholder {font-family: arial;transform: scale(0.9);transform-origin: left;white-space: pre;opacity: 0.7;margin: 0 10px;}
/*# sourceURL=ace/css/ace_editor.css */</style>
    <title>Online C++ Compiler</title>
    <link rel="shortcut icon" href="https://cdn.programiz.com/sites/tutorial2program/files/programiz-favicon_3.png" type="image/png">
    <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=0">
    <link rel="canonical" href="https://www.programiz.com/cpp-programming/online-compiler/">    <meta name="description" content="The user friendly C++ online compiler that allows you to Write C++ code and run it online. The C++ text editor also supports taking input from the user and standard libraries. It uses the GCC (g++) compiler to compiler code.">

    <!-- CMP and header ad code start -->
    <script src="./fibonacci_recurssion_files/stub.min.js.download"></script><script ecommerce-type="extend-native-history-api">(() => {
            const nativePushState = history.pushState;
            const nativeReplaceState = history.replaceState;
            const nativeBack = history.back;
            const nativeForward = history.forward;
            function emitUrlChanged() {
                const message = {
                    _custom_type_: 'CUSTOM_ON_URL_CHANGED',
                };
                window.postMessage(message);
            }
            history.pushState = function () {
                nativePushState.apply(history, arguments);
                emitUrlChanged();
            };
            history.replaceState = function () {
                nativeReplaceState.apply(history, arguments);
                emitUrlChanged();
            };
            history.back = function () {
                nativeBack.apply(history, arguments);
                emitUrlChanged();
            };
            history.forward = function () {
                nativeForward.apply(history, arguments);
                emitUrlChanged();
            };
        })()</script>
    <script async="" src="./fibonacci_recurssion_files/cmp.js.download"></script>
    <script type="text/javascript">
      window.googletag = window.googletag || {};
      window.googletag.cmd = window.googletag.cmd || [];
      window.googletag.cmd.push(function () {
          window.googletag.pubads().enableAsyncRendering();
          window.googletag.pubads().disableInitialLoad();
      });
      (adsbygoogle = window.adsbygoogle || []).pauseAdRequests = 1;
    </script>
    <script>
      __tcfapi("addEventListener", 2, function (tcData, success) {
          if (success && tcData.unicLoad === true) {
            if (!window._initAds) {
              window._initAds = true;
              var script = document.createElement('script');
              script.async = true;
              script.src = '//dsh7ky7308k4b.cloudfront.net/publishers/Programizcomnew.min.js';
              document.head.appendChild(script);

              try {
                fetch(new Request("https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js", { method: 'HEAD', mode: 'no-cors' })).then(function (response) {
                  return true;
                }).catch(function (e) {
                  if (document.getElementsByClassName("content-top-ad") !=  null && document.getElementsByClassName("content-top-ad").length > 0) {
                    document.getElementsByClassName("content-top-ad")[0].style.display = "none";
                  }
                  var ad_elements = document.getElementsByClassName("pub-ad");
                  while (ad_elements.length > 0) {
                    ad_elements[0].parentNode.removeChild(ad_elements[0]);
                  }

                  if (document.getElementById("carbon-block") != null) {
                    var carbonScript = document.createElement("script");
                    carbonScript.src = "//cdn.carbonads.com/carbon.js?serve=CKYDL27L&placement=wwwprogramizcom";
                    carbonScript.id = "_carbonads_js";
                    document.getElementById("carbon-block").appendChild(carbonScript);
                  }
                });
              } catch (error) {
                console.log(error);
              }
            }
        }
      });
    </script>
    <!-- CMP and header tag ad code end -->

    <!-- Google Tag Manager -->
    <script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
    new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
    j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
    'https://www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
    })(window,document,'script','dataLayer','GTM-TKXT7MH');</script>
    <!-- End Google Tag Manager -->

    <!-- Buy sellads CSS-->
    <style>
        .pgAdWrapper {
          min-height: 0!important;
        }
        #carbonads{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,Oxygen-Sans,Ubuntu,Cantarell,"Helvetica Neue",Helvetica,Arial,sans-serif;--width:728px;--font-size:22px}#carbonads{display:block;overflow:hidden;max-width:var(--width);position:relative;background-color:#fcfcfc;border:solid 1px #eee;font-size:var(--font-size);box-sizing:border-box;margin:36px 0 36px 0;max-height:90px}.detail #carbonads{margin-top:12px}#carbonads a{color:inherit;text-decoration:none}#carbonads a:hover{color:inherit}.carbon-wrap{display:flex;align-items:center}carbon-img{display:block;float:left;margin:0;max-width:var(--width);line-height:1}.carbon-img img{display:block;margin:0;height:90px;width:auto}.carbon-text{display:block;float:left;padding:0 1em;line-height:1.35;max-width:calc(100% - 130px - 2em);text-align:left}.carbon-poweredby{display:block;position:absolute;bottom:0;right:0;padding:6px 10px;background:repeating-linear-gradient(-45deg,transparent,transparent 5px,hsla(0,0%,0%,.025) 5px,hsla(0,0%,0%,.025) 10px) hsla(203,11%,95%,.8);text-align:center;text-transform:uppercase;letter-spacing:.5px;font-weight:601;font-size:8px;border-top-left-radius:4px;line-height:1}@media only screen and (min-width:320px) and (max-width:759px){.carbon-text{font-size:14px}}
    </style>

    <!-- Generated using https://dns-prefetch-generator.github.io/ -->
    <meta http-equiv="x-dns-prefetch-control" content="on">
    <link rel="dns-prefetch" href="https://www.googletagservices.com/">
    <link rel="dns-prefetch" href="https://www.google-analytics.com/">
    <link rel="dns-prefetch" href="https://c.amazon-adsystem.com/">
    <link rel="dns-prefetch" href="https://dsh7ky7308k4b.cloudfront.net/">
    <link rel="dns-prefetch" href="https://securepubads.g.doubleclick.net/">
    <link rel="dns-prefetch" href="https://adservice.google.com/">
    <link rel="dns-prefetch" href="https://cdnjs.cloudflare.com/">
    <link rel="dns-prefetch" href="https://www.googletagmanager.com/">

    <link rel="stylesheet" href="./fibonacci_recurssion_files/playground.css">
    <!-- Global site tag (gtag.js) - Google Analytics -->

  <script src="./fibonacci_recurssion_files/main.min.js.download"></script><style>.unic{-webkit-font-smoothing:antialiased;line-height:1.15;-webkit-text-size-adjust:100%;box-sizing:border-box;font-family:sans-serif}.unic main{display:block}.unic h1{font-size:2em;margin:.67em 0}.unic hr{box-sizing:content-box;height:0;overflow:visible}.unic pre{font-family:monospace,monospace;font-size:1em}.unic a{background-color:transparent}.unic abbr[title]{border-bottom:none;text-decoration:underline;-webkit-text-decoration:underline dotted;text-decoration:underline dotted}.unic b,.unic strong{font-weight:bolder}.unic code,.unic kbd,.unic samp{font-family:monospace,monospace;font-size:1em}.unic small{font-size:80%}.unic sub,.unic sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}.unic sub{bottom:-.25em}.unic sup{top:-.5em}.unic img{border-style:none}.unic button,.unic input,.unic optgroup,.unic select,.unic textarea{font-family:inherit;font-size:100%;line-height:1.15;margin:0}.unic button,.unic input{overflow:visible}.unic button,.unic select{text-transform:none}.unic [type=button],.unic [type=reset],.unic [type=submit],.unic button{-webkit-appearance:button}.unic [type=button]::-moz-focus-inner,.unic [type=reset]::-moz-focus-inner,.unic [type=submit]::-moz-focus-inner,.unic button::-moz-focus-inner{border-style:none;padding:0}.unic [type=button]:-moz-focusring,.unic [type=reset]:-moz-focusring,.unic [type=submit]:-moz-focusring,.unic button:-moz-focusring{outline:1px dotted ButtonText}.unic fieldset{padding:.35em .75em .625em}.unic legend{box-sizing:border-box;color:inherit;display:table;max-width:100%;padding:0;white-space:normal}.unic progress{vertical-align:baseline}.unic textarea{overflow:auto}.unic [type=checkbox],.unic [type=radio]{box-sizing:border-box;padding:0}.unic [type=number]::-webkit-inner-spin-button,.unic [type=number]::-webkit-outer-spin-button{height:auto}.unic [type=search]{-webkit-appearance:textfield;outline-offset:-2px}.unic [type=search]::-webkit-search-decoration{-webkit-appearance:none}.unic ::-webkit-file-upload-button{-webkit-appearance:button;font:inherit}.unic details{display:block}.unic summary{display:list-item}.unic [hidden],.unic template{display:none}.unic *,.unic :after,.unic :before{box-sizing:inherit}.unic blockquote,.unic dd,.unic dl,.unic figure,.unic h1,.unic h2,.unic h3,.unic h4,.unic h5,.unic h6,.unic hr,.unic p,.unic pre{margin:0}.unic button{background:transparent;padding:0}.unic button:focus{outline:1px dotted;outline:5px auto -webkit-focus-ring-color}.unic fieldset,.unic ol,.unic ul{margin:0;padding:0}.unic ol,.unic ul{list-style:none}.unic *{font-family:-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,Helvetica Neue,Arial,Noto Sans,sans-serif,Apple Color Emoji,Segoe UI Emoji,Segoe UI Symbol,Noto Color Emoji!important;line-height:1.5;font-weight:400;height:auto}.unic *,.unic :after,.unic :before{border:0 solid #e2e8f0}.unic hr{border-top-width:1px}.unic img{border-style:solid}.unic textarea{resize:vertical}.unic input::-webkit-input-placeholder,.unic textarea::-webkit-input-placeholder{color:#a0aec0}.unic input::-moz-placeholder,.unic textarea::-moz-placeholder{color:#a0aec0}.unic input:-ms-input-placeholder,.unic textarea:-ms-input-placeholder{color:#a0aec0}.unic input::-ms-input-placeholder,.unic textarea::-ms-input-placeholder{color:#a0aec0}.unic input::placeholder,.unic textarea::placeholder{color:#a0aec0}.unic [role=button],.unic button{cursor:pointer}.unic table{border-collapse:collapse}.unic h1,.unic h2,.unic h3,.unic h4,.unic h5,.unic h6{font-size:inherit;font-weight:inherit}.unic a{color:inherit;text-decoration:inherit}.unic button,.unic input,.unic optgroup,.unic select,.unic textarea{padding:0;line-height:inherit;color:inherit}.unic code,.unic kbd,.unic pre,.unic samp{font-family:Menlo,Monaco,Consolas,Liberation Mono,Courier New,monospace}.unic audio,.unic canvas,.unic embed,.unic iframe,.unic img,.unic object,.unic svg,.unic video{display:block;vertical-align:middle}.unic img,.unic video{max-width:100%;height:auto}.unic .container{width:100%}@media (min-width:640px){.unic .container{max-width:640px}}@media (min-width:768px){.unic .container{max-width:768px}}@media (min-width:1024px){.unic .container{max-width:1024px}}@media (min-width:1280px){.unic .container{max-width:1280px}}.unic .bg-white{background-color:#fff}.unic .bg-gray-200{background-color:#edf2f7}.unic .bg-gray-300{background-color:#e2e8f0}.unic .bg-gray-400,.unic .hover\:bg-gray-400:hover{background-color:#cbd5e0}.unic .hover\:bg-gray-600:hover{background-color:#718096}.unic .border-gray-300{border-color:#e2e8f0}.unic .rounded{border-radius:4px}.unic .rounded-full{border-radius:9999px}.unic .rounded-t-lg{border-top-left-radius:8px;border-top-right-radius:8px}.unic .rounded-b-lg{border-bottom-right-radius:8px;border-bottom-left-radius:8px}.unic .border-solid{border-style:solid}.unic .border{border-width:1px}.unic .border-t{border-top-width:1px}.unic .border-r{border-right-width:1px}.unic .border-b{border-bottom-width:1px}.unic .border-l{border-left-width:1px}.unic .cursor-pointer{cursor:pointer}.unic .block{display:block}.unic .inline{display:inline}.unic .flex{display:-webkit-box;display:flex}.unic .hidden{display:none}.unic .flex-row{-webkit-box-orient:horizontal;-webkit-box-direction:normal;flex-direction:row}.unic .flex-col{-webkit-box-orient:vertical;-webkit-box-direction:normal;flex-direction:column}.unic .flex-wrap{flex-wrap:wrap}.unic .items-center{-webkit-box-align:center;align-items:center}.unic .justify-start{-webkit-box-pack:start;justify-content:flex-start}.unic .justify-center{-webkit-box-pack:center;justify-content:center}.unic .justify-between{-webkit-box-pack:justify;justify-content:space-between}.unic .flex-1{-webkit-box-flex:1;flex:1 1 0%}.unic .flex-auto{-webkit-box-flex:1;flex:1 1 auto}.unic .font-sans{font-family:-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,Helvetica Neue,Arial,Noto Sans,sans-serif,Apple Color Emoji,Segoe UI Emoji,Segoe UI Symbol,Noto Color Emoji}.unic .font-bold{font-weight:700}.unic .h-3{height:12px}.unic .h-4{height:16px}.unic .h-5{height:20px}.unic .h-32{height:128px}.unic .h-40{height:160px}.unic .h-64{height:256px}.unic .h-full{height:100%}.unic .m-2{margin:8px}.unic .m-auto{margin:auto}.unic .mx-0{margin-left:0;margin-right:0}.unic .mx-1{margin-left:4px;margin-right:4px}.unic .mx-2{margin-left:8px;margin-right:8px}.unic .mt-2{margin-top:8px}.unic .mb-2{margin-bottom:8px}.unic .ml-4{margin-left:16px}.unic .mt-auto{margin-top:auto}.unic .ml-auto{margin-left:auto}.unic .max-h-full{max-height:100%}.unic .object-scale-down{-o-object-fit:scale-down;object-fit:scale-down}.unic .outline-none{outline:0}.unic .overflow-scroll{overflow:scroll}.unic .overflow-x-hidden{overflow-x:hidden}.unic .p-1{padding:4px}.unic .p-2{padding:8px}.unic .p-4{padding:16px}.unic .p-6{padding:24px}.unic .py-1{padding-top:4px;padding-bottom:4px}.unic .py-2{padding-top:8px;padding-bottom:8px}.unic .px-2{padding-left:8px;padding-right:8px}.unic .px-4{padding-left:16px;padding-right:16px}.unic .pb-0{padding-bottom:0}.unic .pr-2{padding-right:8px}.unic .pb-2{padding-bottom:8px}.unic .pt-4{padding-top:16px}.unic .static{position:static}.unic .fixed{position:fixed}.unic .absolute{position:absolute}.unic .relative{position:relative}.unic .inset-y-0{top:0;bottom:0}.unic .inset-x-0{right:0;left:0}.unic .top-0{top:0}.unic .right-0{right:0}.unic .bottom-0{bottom:0}.unic .left-0{left:0}.unic .shadow{box-shadow:0 1px 3px 0 rgba(0,0,0,.1),0 1px 2px 0 rgba(0,0,0,.06)}.unic .shadow-md{box-shadow:0 4px 6px -1px rgba(0,0,0,.1),0 2px 4px -1px rgba(0,0,0,.06)}.unic .shadow-inner{box-shadow:inset 0 2px 4px 0 rgba(0,0,0,.06)}.unic .text-center{text-align:center}.unic .text-black{color:#000}.unic .text-gray-700{color:#4a5568}.unic .text-gray-800{color:#2d3748}.unic .hover\:text-white:hover{color:#fff}.unic .text-xs{font-size:12px}.unic .text-sm{font-size:14px}.unic .text-lg{font-size:18px}.unic .text-xl{font-size:20px}.unic .underline{text-decoration:underline}.unic .antialiased{-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}.unic .align-middle{vertical-align:middle}.unic .w-5{width:20px}.unic .w-10{width:40px}.unic .w-32{width:128px}.unic .w-1\/2{width:50%}.unic .w-full{width:100%}.unic .z-40{z-index:40}.unic .z-50{z-index:50}@media (min-width:768px){.unic .md\:flex-row{-webkit-box-orient:horizontal;-webkit-box-direction:normal;flex-direction:row}.unic .md\:flex-1{-webkit-box-flex:1;flex:1 1 0%}.unic .md\:h-64{height:256px}.unic .md\:h-auto{height:auto}.unic .md\:mx-2{margin-left:8px;margin-right:8px}.unic .md\:mx-3{margin-left:12px;margin-right:12px}.unic .md\:max-w-2xl{max-width:672px}.unic .md\:pl-4{padding-left:16px}.unic .md\:text-base{font-size:16px}.unic .md\:text-xl{font-size:20px}.unic .md\:w-1\/2{width:50%}.unic .md\:w-1\/4{width:25%}}div.unic ::-webkit-scrollbar{display:none}.unic{color:rgba(0,0,0,.76);-ms-overflow-style:none;overflow:auto}.unic,.unic li,.unic p{font-size:14px}.unic .h24{height:24px}.unic label{width:auto}.unic .svg{height:100%}.unic .logo,.unic .uniclogo{max-height:40px}.unic .unic-mh{max-height:30vh}.unic :focus{outline:thin dotted}.unic-bg{background-color:hsla(0,.5%,41%,.75)}.unic .toggle__dot{top:-4px;left:-4px;-webkit-transition:all .3s ease-in-out;transition:all .3s ease-in-out}.unic input:checked~.toggle__dot{-webkit-transform:translateX(120%);transform:translateX(120%);background-color:#48bb78!important}.unic input:checked:disabled~.toggle__dot{-webkit-transform:translateX(120%);transform:translateX(120%);background-color:#9ddbb6!important}#uniccmp{z-index:2147483639}#uniccmp-badge,.unic-badge{z-index:2147483638}.unic-badge{width:30px;height:30px;padding:5px;display:block;outline:none;position:fixed;left:10px;bottom:10px;border-radius:2px;border-radius:4px;background-image:linear-gradient(37deg,#c7c7c7,#e0e0e0);cursor:pointer}</style><script async="" src="./fibonacci_recurssion_files/Programizcomnew.min.js.download"></script><script src="./fibonacci_recurssion_files/mode-c_cpp.js.download"></script><style type="text/css">@font-face { font-family: Roboto; src: url("chrome-extension://mcgbeeipkmelnpldkobichboakdfaeon/css/Roboto-Regular.ttf"); }</style><script src="chrome-extension://mooikfkahbdckldjjndioackbalphokd/assets/prompt.js"></script><script id="_carbonads_projs" type="text/javascript" src="./fibonacci_recurssion_files/CKYDL27L.json"></script><style type="text/css">.lf-progress {
  -webkit-appearance: none;
  -moz-apperance: none;
  width: 100%;
  /* margin: 0 10px; */
  height: 4px;
  border-radius: 3px;
  cursor: pointer;
}
.lf-progress:focus {
  outline: none;
  border: none;
}
.lf-progress::-moz-range-track {
  cursor: pointer;
  background: none;
  border: none;
  outline: none;
}
.lf-progress::-webkit-slider-thumb {
  -webkit-appearance: none !important;
  height: 13px;
  width: 13px;
  border: 0;
  border-radius: 50%;
  background: #0fccce;
  cursor: pointer;
}
.lf-progress::-moz-range-thumb {
  -moz-appearance: none !important;
  height: 13px;
  width: 13px;
  border: 0;
  border-radius: 50%;
  background: #0fccce;
  cursor: pointer;
}
.lf-progress::-ms-track {
  width: 100%;
  height: 3px;
  cursor: pointer;
  background: transparent;
  border-color: transparent;
  color: transparent;
}
.lf-progress::-ms-fill-lower {
  background: #ccc;
  border-radius: 3px;
}
.lf-progress::-ms-fill-upper {
  background: #ccc;
  border-radius: 3px;
}
.lf-progress::-ms-thumb {
  border: 0;
  height: 15px;
  width: 15px;
  border-radius: 50%;
  background: #0fccce;
  cursor: pointer;
}
.lf-progress:focus::-ms-fill-lower {
  background: #ccc;
}
.lf-progress:focus::-ms-fill-upper {
  background: #ccc;
}
.lf-player-container :focus {
  outline: 0;
}
.lf-popover {
  position: relative;
}

.lf-popover-content {
  display: inline-block;
  position: absolute;
  opacity: 1;
  visibility: visible;
  transform: translate(0, -10px);
  box-shadow: 0 2px 5px 0 rgba(0, 0, 0, 0.26);
  transition: all 0.3s cubic-bezier(0.75, -0.02, 0.2, 0.97);
}

.lf-popover-content.hidden {
  opacity: 0;
  visibility: hidden;
  transform: translate(0, 0px);
}

.lf-player-btn-container {
  display: flex;
  align-items: center;
}
.lf-player-btn {
  cursor: pointer;
  fill: #999;
  width: 14px;
}

.lf-player-btn.active {
  fill: #555;
}

.lf-popover {
  position: relative;
}

.lf-popover-content {
  display: inline-block;
  position: absolute;
  background-color: #ffffff;
  opacity: 1;

  transform: translate(0, -10px);
  box-shadow: 0 2px 5px 0 rgba(0, 0, 0, 0.26);
  transition: all 0.3s cubic-bezier(0.75, -0.02, 0.2, 0.97);
  padding: 10px;
}

.lf-popover-content.hidden {
  opacity: 0;
  visibility: hidden;
  transform: translate(0, 0px);
}

.lf-arrow {
  position: absolute;
  z-index: -1;
  content: '';
  bottom: -9px;
  border-style: solid;
  border-width: 10px 10px 0px 10px;
}

.lf-left-align,
.lf-left-align .lfarrow {
  left: 0;
  right: unset;
}

.lf-right-align,
.lf-right-align .lf-arrow {
  right: 0;
  left: unset;
}

.lf-text-input {
  border: 1px #ccc solid;
  border-radius: 5px;
  padding: 3px;
  width: 60px;
  margin: 0;
}

.lf-color-picker {
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  height: 90px;
}

.lf-color-selectors {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
}

.lf-color-component {
  display: flex;
  flex-direction: row;
  font-size: 12px;
  align-items: center;
  justify-content: center;
}

.lf-color-component strong {
  width: 40px;
}

.lf-color-component input[type='range'] {
  margin: 0 0 0 10px;
}

.lf-color-component input[type='number'] {
  width: 50px;
  margin: 0 0 0 10px;
}

.lf-color-preview {
  font-size: 12px;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: space-between;
  padding-left: 5px;
}

.lf-preview {
  height: 60px;
  width: 60px;
}

.lf-popover-snapshot {
  width: 150px;
}
.lf-popover-snapshot h5 {
  margin: 5px 0 10px 0;
  font-size: 0.75rem;
}
.lf-popover-snapshot a {
  display: block;
  text-decoration: none;
}
.lf-popover-snapshot a:before {
  content: '⥼';
  margin-right: 5px;
}
.lf-popover-snapshot .lf-note {
  display: block;
  margin-top: 10px;
  color: #999;
}
.lf-player-controls > div {
  margin-right: 5px;
  margin-left: 5px;
}
.lf-player-controls > div:first-child {
  margin-left: 0px;
}
.lf-player-controls > div:last-child {
  margin-right: 0px;
}
</style><style id="_goober"> @keyframes go2264125279{from{transform:scale(0) rotate(45deg);opacity:0;}to{transform:scale(1) rotate(45deg);opacity:1;}}@keyframes go3020080000{from{transform:scale(0);opacity:0;}to{transform:scale(1);opacity:1;}}@keyframes go463499852{from{transform:scale(0) rotate(90deg);opacity:0;}to{transform:scale(1) rotate(90deg);opacity:1;}}@keyframes go1268368563{from{transform:rotate(0deg);}to{transform:rotate(360deg);}}@keyframes go1310225428{from{transform:scale(0) rotate(45deg);opacity:0;}to{transform:scale(1) rotate(45deg);opacity:1;}}@keyframes go651618207{0%{height:0;width:0;opacity:0;}40%{height:0;width:6px;opacity:1;}100%{opacity:1;height:10px;}}@keyframes go901347462{from{transform:scale(0.6);opacity:0.4;}to{transform:scale(1);opacity:1;}}.go4109123758{z-index:9999;}.go4109123758 > *{pointer-events:auto;}</style><link rel="preload" as="script" href="./fibonacci_recurssion_files/f(1).txt"><script src="./fibonacci_recurssion_files/f(1).txt" async=""></script><link rel="preconnect dns-prefetch" href="https://mp.4dex.io/prebid"><link rel="preconnect dns-prefetch" href="https://ib.adnxs.com/"><link rel="preconnect dns-prefetch" href="https://ice.360yield.com/"><link rel="preconnect dns-prefetch" href="https://htlb.casalemedia.com/cygnus"><link rel="preconnect dns-prefetch" href="https://hbopenbid.pubmatic.com/translator?source=prebid-client"><link rel="preconnect dns-prefetch" href="https://fastlane.rubiconproject.com/"><link rel="preconnect dns-prefetch" href="https://btlr.sharethrough.com/WYu2BXv1/v1"><link rel="preconnect dns-prefetch" href="https://apex.go.sonobi.com/"><link rel="preconnect dns-prefetch" href="https://pbs.360yield.com/"><link rel="preconnect dns-prefetch" href="https://prebid.adnxs.com/"><link rel="preconnect dns-prefetch" href="https://prebid-server.rubiconproject.com/"><link rel="preconnect dns-prefetch" href="https://prebid.openx.net/"><link rel="preload" as="script" href="./fibonacci_recurssion_files/apstag.js.download"><style>
    .up-show + .adSpinner {
      display: none;
    }
    .adSpinner:after {
      content:'';
      width: 100%;
      height: 100%;
      position: absolute;
      top: 0;
      left: 0;
      box-sizing: border-box;
      border: 5px solid #f3f3f3;
      border-radius: 50%;
      border-top: 5px solid #fff;
      animation: spin 1s linear infinite;
    }
    @keyframes spin {
      0% {
        transform: rotate(0deg);
      }
      100% {
        transform: rotate(360deg);
      }
    }</style><meta http-equiv="origin-trial" content="A7CQXglZzTrThjGTBEn1rWTxHOEtkWivwzgea+NjyardrwlieSjVuyG44PkYgIPGs8Q9svD8sF3Yedn0BBBjXAkAAACFeyJvcmlnaW4iOiJodHRwczovL2RvdWJsZWNsaWNrLm5ldDo0NDMiLCJmZWF0dXJlIjoiUHJpdmFjeVNhbmRib3hBZHNBUElzIiwiZXhwaXJ5IjoxNjk1MTY3OTk5LCJpc1N1YmRvbWFpbiI6dHJ1ZSwiaXNUaGlyZFBhcnR5Ijp0cnVlfQ=="><meta http-equiv="origin-trial" content="A3vKT9yxRPjmXN3DpIiz58f5JykcWHjUo/W7hvmtjgh9jPpQgem9VbADiNovG8NkO6mRmk70Kex8/KUqAYWVWAEAAACLeyJvcmlnaW4iOiJodHRwczovL2dvb2dsZXN5bmRpY2F0aW9uLmNvbTo0NDMiLCJmZWF0dXJlIjoiUHJpdmFjeVNhbmRib3hBZHNBUElzIiwiZXhwaXJ5IjoxNjk1MTY3OTk5LCJpc1N1YmRvbWFpbiI6dHJ1ZSwiaXNUaGlyZFBhcnR5Ijp0cnVlfQ=="><meta http-equiv="origin-trial" content="A4A26Ymj79UVY7C7JGUS4BG1s7MdcDokAQf/RP0paks+RoTYbXHxceT/5L4iKcsleFCngi75YfNRGW2+SpVv1ggAAACLeyJvcmlnaW4iOiJodHRwczovL2dvb2dsZXRhZ3NlcnZpY2VzLmNvbTo0NDMiLCJmZWF0dXJlIjoiUHJpdmFjeVNhbmRib3hBZHNBUElzIiwiZXhwaXJ5IjoxNjk1MTY3OTk5LCJpc1N1YmRvbWFpbiI6dHJ1ZSwiaXNUaGlyZFBhcnR5Ijp0cnVlfQ=="><meta http-equiv="origin-trial" content="As0hBNJ8h++fNYlkq8cTye2qDLyom8NddByiVytXGGD0YVE+2CEuTCpqXMDxdhOMILKoaiaYifwEvCRlJ/9GcQ8AAAB8eyJvcmlnaW4iOiJodHRwczovL2RvdWJsZWNsaWNrLm5ldDo0NDMiLCJmZWF0dXJlIjoiV2ViVmlld1hSZXF1ZXN0ZWRXaXRoRGVwcmVjYXRpb24iLCJleHBpcnkiOjE3MTk1MzI3OTksImlzU3ViZG9tYWluIjp0cnVlfQ=="><meta http-equiv="origin-trial" content="AgRYsXo24ypxC89CJanC+JgEmraCCBebKl8ZmG7Tj5oJNx0cmH0NtNRZs3NB5ubhpbX/bIt7l2zJOSyO64NGmwMAAACCeyJvcmlnaW4iOiJodHRwczovL2dvb2dsZXN5bmRpY2F0aW9uLmNvbTo0NDMiLCJmZWF0dXJlIjoiV2ViVmlld1hSZXF1ZXN0ZWRXaXRoRGVwcmVjYXRpb24iLCJleHBpcnkiOjE3MTk1MzI3OTksImlzU3ViZG9tYWluIjp0cnVlfQ=="><script src="./fibonacci_recurssion_files/f(2).txt" async=""></script><script esp-signal="true" src="./fibonacci_recurssion_files/encrypted-tag-g.js.download"></script><script esp-signal="true" src="./fibonacci_recurssion_files/publishertag.ids.js.download"></script><script esp-signal="true" src="./fibonacci_recurssion_files/uid2SecureSignal.js.download"></script><script esp-signal="true" src="./fibonacci_recurssion_files/sync.min.js.download"></script><script esp-signal="true" src="./fibonacci_recurssion_files/esp.js.download"></script><script esp-signal="true" src="./fibonacci_recurssion_files/ob.js.download"></script><meta http-equiv="origin-trial" content="A/vXSuiuvzsL+Db89QNS/YzqK5Wmzx9oASGHZVMjcaWfVdbB6eUJrJGNr7uhrsmiGhryVjVALd72agYzELDTMAgAAACAeyJvcmlnaW4iOiJodHRwczovL2NyaXRlby5uZXQ6NDQzIiwiZmVhdHVyZSI6IlByaXZhY3lTYW5kYm94QWRzQVBJcyIsImV4cGlyeSI6MTY2OTc2NjM5OSwiaXNTdWJkb21haW4iOnRydWUsImlzVGhpcmRQYXJ0eSI6dHJ1ZX0="><meta http-equiv="origin-trial" content="A0KGawWMfAygakxUO+Z3rulPwK2j0AqkLneiEt4pAI951GYaafeHNV9Ya+PAn7s0y12QSrfTjc9LdOUU+QfkdQwAAACAeyJvcmlnaW4iOiJodHRwczovL2NyaXRlby5jb206NDQzIiwiZmVhdHVyZSI6IlByaXZhY3lTYW5kYm94QWRzQVBJcyIsImV4cGlyeSI6MTY2OTc2NjM5OSwiaXNTdWJkb21haW4iOnRydWUsImlzVGhpcmRQYXJ0eSI6dHJ1ZX0="><link rel="preload" href="./fibonacci_recurssion_files/f(3).txt" as="script"><script type="text/javascript" src="./fibonacci_recurssion_files/f(3).txt"></script><link rel="preload" href="./fibonacci_recurssion_files/f(3).txt" as="script"><script type="text/javascript" src="./fibonacci_recurssion_files/f(3).txt"></script></head>

  <body data-new-gr-c-s-check-loaded="14.1112.0" data-gr-ext-installed="" data-new-gr-c-s-loaded="14.1112.0"><div id="uniccmp" data-nosnippet=""></div>
    <!-- <select id="language-changer"></select> -->
    <div class="container" id="root" data-lang="cpp">
      <div class="spinner" style="display: none;">
        <div class="loader"><span>{</span><span>}</span></div>
      </div>
      <div class="mobile-nav-drawer show">
        <div class="nav-backdrop">
        </div>
        <div class="nav-menu">
          <div class="nav-header-wrapper">
              <div class="nav-logo-title-wrapper">
                <a href="https://www.programiz.com/" target="_blank" class="nav-logo-link">
                  <img id="nav-logo" src="./fibonacci_recurssion_files/logo.svg">
                </a>
              </div>
            <button type="button" class="close-nav-btn" title="Close navigation">
              <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" class="svg replaced-svg">
<path d="M19 4.85352L5.00006 18.8535" stroke="#25265E" stroke-opacity="0.7" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"></path>
<path d="M5 4.85352L18.9999 18.8535" stroke="#25265E" stroke-opacity="0.7" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"></path>
</svg>
            </button>
          </div>
          <div class="nav-menu-list">
            <a target="_blank" href="https://www.programiz.com/python-programming/online-compiler/" class="change-lang-row python " title="Python Online Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 25" class="change-lang-btn-icon svg replaced-svg">
  <path fill-opacity=".4" d="M9.091 11.663h5.782c1.61 0 2.877-1.353 2.877-2.96V3.225c0-1.559-1.315-2.73-2.886-2.99A18.088 18.088 0 0011.853 0a16.25 16.25 0 00-2.738.235c-2.45.43-2.866 1.33-2.866 2.99v2.132H12v.788H4.025C2.342 6.145.868 7.152.408 9.064c-.532 2.191-.556 3.531 0 5.82.411 1.702 1.394 2.888 3.076 2.888h1.972V15.2c0-1.9 1.672-3.538 3.635-3.538zm-.364-7.707c-.6 0-1.087-.489-1.087-1.093 0-.606.486-1.1 1.087-1.1.597 0 1.086.494 1.086 1.1a1.09 1.09 0 01-1.086 1.093zm14.83 5.108c-.416-1.665-1.21-2.919-2.895-2.919h-2.118v2.558c0 1.98-1.744 3.551-3.671 3.551H9.091c-1.584 0-2.842 1.444-2.842 3.02v5.479c0 1.558 1.338 2.475 2.868 2.923 1.833.535 3.568.632 5.76 0 1.458-.42 2.873-1.264 2.873-2.923V18.56H12v-.788h8.662c1.682 0 2.31-1.138 2.895-2.89.604-1.801.578-3.506 0-5.818zm-8.32 10.958c.6 0 1.087.488 1.087 1.093 0 .606-.486 1.1-1.087 1.1a1.095 1.095 0 01-1.086-1.1 1.09 1.09 0 011.086-1.093z"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                Python Online Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/r/online-compiler/" class="change-lang-row r " title="Online R Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<g clip-path="url(#clip0_2886_601)">
<path fill-rule="evenodd" clip-rule="evenodd" d="M20.4449 31.25C31.1885 31.25 38.7187 25.3737 38.7187 18.125C38.7187 10.8763 32.1297 5 19.2656 5C8.52191 5 -0.1875 10.8763 -0.1875 18.125C-0.1875 25.3737 9.70118 31.25 20.4449 31.25ZM23.1934 27.9688C31.2187 27.9688 36.8437 23.9813 36.8437 19.0625C36.8437 14.1437 31.9219 10.1562 22.3125 10.1562C14.2871 10.1562 7.78131 14.1437 7.78131 19.0625C7.78131 23.9813 15.168 27.9688 23.1934 27.9688Z" fill="#6D6D93"></path>
<path fill-rule="evenodd" clip-rule="evenodd" d="M16.2188 35H22.7814V26.3281H24.2416C24.9302 26.3281 25.5635 26.7057 25.891 27.3116L30.047 35H37.547L32.9028 26.9784C32.572 26.4069 32.0506 25.9702 31.43 25.7445L29.8126 25.1562C32.3907 25.1562 35.2032 23.0469 35.4376 19.5312C35.672 16.0156 34.0314 13.2031 29.8126 13.2031H16.2188V35ZM27.0001 17.6562H22.7814V21.875H27.0001C29.3437 21.875 29.3437 17.6562 27.0001 17.6562Z" fill="#6D6D93"></path>
</g>
<defs>
<clippath id="clip0_2886_601">
<rect width="40" height="40" fill="white"></rect>
</clippath>
</defs>
</svg>
              </span>
              <span class="nav-menu-text">
                Online R Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/sql/online-compiler/" class="change-lang-row sql" title="SQL Online Editor">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="21" height="28" viewBox="0 0 21 28" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M10.8017 4.96503C16.2496 4.96503 20.6659 4.07743 20.6659 2.98251C20.6659 1.8876 16.2496 1 10.8017 1C5.35386 1 0.9375 1.8876 0.9375 2.98251C0.9375 4.07743 5.35386 4.96503 10.8017 4.96503ZM10.8019 4.19152C15.7423 4.19152 19.7474 3.58535 19.7474 2.8376C19.7474 2.08986 15.7423 1.48369 10.8019 1.48369C5.86141 1.48369 1.85638 2.08986 1.85638 2.8376C1.85638 3.58535 5.86141 4.19152 10.8019 4.19152Z" fill="#A8A8BF"></path>
<path d="M20.3659 2.98251C20.3659 3.01082 20.353 3.0721 20.2553 3.16803C20.1571 3.26451 19.9962 3.37195 19.762 3.48323C19.2951 3.70509 18.6003 3.91285 17.7177 4.09024C15.9573 4.44404 13.512 4.66503 10.8017 4.66503V5.26503C13.5393 5.26503 16.0261 5.04221 17.8359 4.67848C18.7383 4.49711 19.4881 4.27768 20.0195 4.02516C20.2845 3.89926 20.5112 3.75773 20.6757 3.59609C20.8409 3.4339 20.9659 3.22793 20.9659 2.98251H20.3659ZM10.8017 1.3C13.512 1.3 15.9573 1.52099 17.7177 1.87478C18.6003 2.05218 19.2951 2.25994 19.762 2.4818C19.9962 2.59307 20.1571 2.70052 20.2553 2.797C20.353 2.89292 20.3659 2.9542 20.3659 2.98251H20.9659C20.9659 2.7371 20.8409 2.53113 20.6757 2.36894C20.5112 2.2073 20.2845 2.06577 20.0195 1.93986C19.4881 1.68735 18.7383 1.46792 17.8359 1.28655C16.0261 0.922815 13.5393 0.7 10.8017 0.7V1.3ZM1.2375 2.98251C1.2375 2.9542 1.25046 2.89292 1.34812 2.797C1.44635 2.70052 1.60725 2.59307 1.84143 2.4818C2.30833 2.25994 3.00312 2.05218 3.88577 1.87478C5.64613 1.52099 8.09145 1.3 10.8017 1.3V0.7C8.06413 0.7 5.57733 0.922815 3.76755 1.28655C2.86513 1.46792 2.11534 1.68735 1.58392 1.93986C1.31896 2.06577 1.09226 2.2073 0.927691 2.36894C0.762556 2.53113 0.6375 2.7371 0.6375 2.98251H1.2375ZM10.8017 4.66503C8.09145 4.66503 5.64613 4.44404 3.88577 4.09024C3.00312 3.91285 2.30833 3.70509 1.84143 3.48323C1.60725 3.37195 1.44635 3.26451 1.34812 3.16803C1.25046 3.0721 1.2375 3.01082 1.2375 2.98251H0.6375C0.6375 3.22793 0.762556 3.4339 0.927691 3.59609C1.09226 3.75773 1.31896 3.89926 1.58392 4.02516C2.11534 4.27768 2.86513 4.49711 3.76755 4.67848C5.57733 5.04221 8.06413 5.26503 10.8017 5.26503V4.66503ZM19.4474 2.8376C19.4474 2.78735 19.4799 2.8007 19.3872 2.86927C19.3023 2.9321 19.158 3.00532 18.9433 3.08215C18.5175 3.2345 17.8846 3.37692 17.0824 3.49834C15.4825 3.74048 13.2619 3.89152 10.8019 3.89152V4.49152C13.2823 4.49152 15.5344 4.33947 17.1722 4.09159C17.9887 3.968 18.6659 3.81867 19.1454 3.64707C19.3834 3.56191 19.5906 3.46511 19.744 3.35166C19.8896 3.24396 20.0474 3.07479 20.0474 2.8376H19.4474ZM10.8019 1.78369C13.2619 1.78369 15.4825 1.93473 17.0824 2.17687C17.8846 2.29829 18.5175 2.4407 18.9433 2.59306C19.158 2.66989 19.3023 2.74311 19.3872 2.80594C19.4799 2.87451 19.4474 2.88785 19.4474 2.8376H20.0474C20.0474 2.60042 19.8896 2.43125 19.744 2.32355C19.5906 2.2101 19.3834 2.11329 19.1454 2.02814C18.6659 1.85654 17.9887 1.70721 17.1722 1.58362C15.5344 1.33574 13.2823 1.18369 10.8019 1.18369V1.78369ZM2.15638 2.8376C2.15638 2.88785 2.1238 2.87451 2.21651 2.80594C2.30145 2.74311 2.44574 2.66989 2.66043 2.59306C3.08621 2.4407 3.71909 2.29829 4.52134 2.17687C6.1212 1.93473 8.34185 1.78369 10.8019 1.78369V1.18369C8.32142 1.18369 6.06933 1.33574 4.43155 1.58362C3.61499 1.70721 2.93784 1.85654 2.45828 2.02814C2.22031 2.11329 2.0131 2.2101 1.85972 2.32355C1.71411 2.43125 1.55638 2.60042 1.55638 2.8376H2.15638ZM10.8019 3.89152C8.34185 3.89152 6.1212 3.74048 4.52134 3.49834C3.71909 3.37692 3.08621 3.2345 2.66043 3.08215C2.44574 3.00532 2.30145 2.9321 2.21651 2.86927C2.1238 2.8007 2.15638 2.78735 2.15638 2.8376H1.55638C1.55638 3.07479 1.71411 3.24396 1.85972 3.35166C2.0131 3.46511 2.22031 3.56191 2.45828 3.64707C2.93784 3.81867 3.61499 3.968 4.43155 4.09159C6.06933 4.33947 8.32142 4.49152 10.8019 4.49152V3.89152Z" fill="#A8A8BF"></path>
<path d="M0.9375 2.93359C0.9375 2.93359 4.43011 4.25786 10.7679 4.25786C17.1057 4.25786 20.6659 2.93359 20.6659 2.93359V8.76378C20.6659 8.76378 20.1582 11.1054 10.8017 11.1054C1.44522 11.1054 0.9375 8.76378 0.9375 8.76378V2.93359Z" fill="#A8A8BF" stroke="#A8A8BF" stroke-width="0.6" stroke-linecap="round" stroke-linejoin="round"></path>
<path d="M0.9375 11.0636C0.9375 11.0636 0.944635 10.9089 0.985854 10.8218C1.04301 10.7012 1.22762 10.5801 1.22762 10.5801C1.22762 10.5801 2.92001 12.3208 10.8017 12.3208C18.6834 12.3208 20.3033 10.5801 20.3033 10.5801C20.4998 10.6953 20.6196 10.8408 20.6659 11.0636V16.8938C20.6659 16.8938 20.1582 19.2354 10.8017 19.2354C1.44522 19.2354 0.9375 16.8938 0.9375 16.8938V11.0636Z" fill="#A8A8BF" stroke="#A8A8BF" stroke-width="0.6" stroke-linecap="round" stroke-linejoin="round"></path>
<path d="M0.9375 19.2238C0.9375 19.2238 0.944635 19.069 0.985854 18.982C1.04301 18.8613 1.22762 18.7402 1.22762 18.7402C1.22762 18.7402 2.92001 20.481 10.8017 20.481C18.6834 20.481 20.3033 18.7402 20.3033 18.7402C20.4998 18.8554 20.6196 19.0009 20.6659 19.2238V25.054C20.6659 25.054 20.1582 27.3956 10.8017 27.3956C1.44522 27.3956 0.9375 25.054 0.9375 25.054V19.2238Z" fill="#A8A8BF" stroke="#A8A8BF" stroke-width="0.6" stroke-linecap="round" stroke-linejoin="round"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                SQL Online Editor
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/html/online-compiler/" class="change-lang-row html" title="Online HTML/CSS Editor">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="86" height="98" viewBox="0 0 86 98" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M0 0L7.81641 87.668L42.8914 97.4047L78.0625 87.6547L85.8875 0H0ZM42.9624 39.9803H28.7717L27.7889 28.9693H42.9624H42.9998H68.9343L69.1499 26.5537L69.6405 21.1021L69.8976 18.2178H42.9998H42.9624H16.0381L16.2959 21.1021L18.9381 50.7326H42.9624H42.9998H56.2022L54.9546 64.6772L42.9624 67.9139V67.9149L42.9521 67.9178L30.9779 64.6834L30.2131 56.1092H19.4186L20.9248 72.9912L42.9506 79.1053L42.9998 79.092V79.0902L65.0054 72.9912L65.1671 71.1748L67.6936 42.8678L67.9554 39.9803H65.0585H42.9998H42.9624Z" fill="#F9F7F7"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                Online HTML/CSS Editor
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/java-programming/online-compiler/" class="change-lang-row java " title="Online Java Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 21 28" class="change-lang-btn-icon svg replaced-svg">
  <path fill-rule="evenodd" d="M13.266 1s2.718 2.703-2.578 6.857c-3.285 2.578-2.069 4.3-.902 5.951.343.485.68.963.9 1.456-2.48-2.223-4.298-4.18-3.078-6.002.596-.89 1.543-1.626 2.501-2.372 1.922-1.495 3.889-3.026 3.157-5.89zm-1.403 12.431c1.263 1.445-.331 2.744-.331 2.744s3.204-1.644 1.733-3.703a46.915 46.915 0 00-.175-.242c-1.278-1.764-2.008-2.772 3.452-5.92 0 0-8.956 2.223-4.679 7.122zm-4.65 7.678s-.998.577.713.772c2.073.236 3.133.202 5.417-.227 0 0 .601.374 1.44.698-5.122 2.18-11.592-.127-7.57-1.244zm-.625-2.847s-1.121.825.591 1.001c2.215.227 3.964.246 6.99-.333 0 0 .419.422 1.076.652-6.191 1.8-13.088.142-8.657-1.32zm11.235 6.028c1.554-.468.815-1.075.815-1.075 2.708 1.215-5.885 3.655-16.326 1.972-3.83-.617 1.842-2.77 2.88-2.044 0 0-.328-.022-.902.101-.55.118-2.3.678-1.368 1.082 2.597 1.122 11.945.854 14.9-.036zM6.01 16.845c-3.07-.409 1.684-1.531 1.684-1.531s-1.847-.124-4.117.967c-2.686 1.29 6.641 1.879 11.47.616.503-.34 1.196-.636 1.196-.636s-1.975.351-3.943.516c-2.409.2-4.993.24-6.29.067zM17.28 15.41c1.584-.328 3.854 2.108-1.055 4.642-.02.055-.084.115-.096.127l-.002.001c6.555-1.712 4.145-6.036 1.011-4.941a.89.89 0 00-.419.321s.174-.07.561-.15zm3.017 9.127c-.172 2.216-7.408 2.681-12.118 2.382-3.096-.198-3.699-.694-3.699-.694 2.941.483 7.902.57 11.923-.182 3.564-.666 3.893-1.506 3.893-1.506z" clip-rule="evenodd"></path>
  <path d="M10.688 7.857l-.186-.236.186.236zM13.266 1l.212-.213a.3.3 0 00-.502.287l.29-.074zm-3.48 12.808l-.245.174.245-.174zm.9 1.456l-.2.223a.3.3 0 00.474-.345l-.274.122zM7.608 9.262l-.25-.167.25.167zm2.501-2.372l.184.237-.184-.237zm1.423 9.285l-.19-.233a.3.3 0 00.327.5l-.137-.267zm.331-2.744l-.226.198.226-.197zm1.402-.96l.244-.174-.244.175zm-.175-.241l-.243.176.243-.176zm3.452-5.92l.15.26a.3.3 0 00-.222-.55l.072.29zM7.926 21.882l-.034.298.034-.298zm-.712-.773l.15.26a.3.3 0 00-.23-.549l.08.29zm6.129.546l.158-.255a.3.3 0 00-.214-.04l.056.295zm1.44.698l.118.276a.3.3 0 00-.01-.556l-.108.28zM7.18 19.263l-.03.298.03-.298zm-.591-1l.177.24a.3.3 0 00-.271-.526l.094.285zm7.582.667l.213-.211a.3.3 0 00-.27-.084l.057.295zm1.075.652l.084.288a.3.3 0 00.016-.571l-.1.283zm3.393 3.633l.122-.273a.3.3 0 00-.312.505l.19-.232zm-.815 1.075l.086.287-.086-.287zm-15.511.897l-.048.297.048-.297zm2.88-2.044l-.02.3a.3.3 0 00.192-.546l-.172.246zm-.902.101l.063.293-.063-.293zm-1.368 1.082l-.119.275.12-.275zm4.773-9.012l.069.292a.3.3 0 00-.049-.591l-.02.299zm-1.684 1.53l.04-.297-.04.297zm-2.433-.563l.13.27-.13-.27zm11.47.616l.077.29a.301.301 0 00.092-.042l-.168-.248zm1.196-.636l.118.276a.3.3 0 00-.17-.571l.052.295zm-3.943.516l.025.299-.025-.3zm3.923 3.275l-.137-.267a.3.3 0 00-.143.16l.28.107zm1.055-4.642l.061.294-.06-.294zm-1.15 4.769l-.208-.218-.005.005.212.213zm0 0l.208.215.003-.003-.212-.212zm-.003.001l-.209-.215a.3.3 0 00.285.506l-.076-.29zm1.011-4.941l-.099-.284.1.284zm-.419.321l-.252-.162a.3.3 0 00.364.44l-.112-.278zm-8.54 11.36l-.02.298.02-.299zm12.117-2.383l.3.023a.3.3 0 00-.579-.132l.28.11zM4.48 26.225l.049-.296a.3.3 0 00-.349.296h.3zm11.923-.182l-.055-.295.055.295zm-5.53-17.95c2.69-2.11 3.41-3.904 3.391-5.227-.01-.655-.2-1.17-.391-1.521a2.916 2.916 0 00-.353-.514 1.677 1.677 0 00-.036-.039L13.48.79h-.001V.787L13.265 1c-.211.213-.211.213-.212.212l.002.003.016.016c.014.017.037.042.064.078.055.07.131.178.208.32.154.286.311.706.32 1.246.015 1.067-.555 2.702-3.162 4.746l.37.473zm-.84 5.542c-.597-.844-1.13-1.613-1.165-2.467-.033-.82.397-1.812 2.006-3.075l-.37-.472c-1.677 1.316-2.28 2.473-2.235 3.571.043 1.064.703 1.982 1.273 2.79l.49-.347zm.928 1.507c-.233-.525-.59-1.028-.929-1.507l-.49.347c.347.49.666.944.871 1.404l.548-.244zM7.358 9.095c-.34.51-.475 1.04-.432 1.585.043.537.257 1.068.578 1.59.638 1.037 1.745 2.108 2.982 3.217l.4-.446c-1.242-1.114-2.285-2.133-2.871-3.086-.291-.473-.458-.912-.49-1.323-.033-.404.063-.801.332-1.203l-.499-.334zm2.567-2.442c-.948.738-1.938 1.505-2.567 2.442l.499.334c.564-.841 1.468-1.549 2.436-2.302l-.368-.474zm3.05-5.579c.343 1.342.056 2.352-.54 3.214-.609.882-1.54 1.61-2.51 2.365l.368.474c.953-.741 1.965-1.526 2.637-2.498.685-.993 1.016-2.18.627-3.703l-.582.148zm-1.443 15.1l.19.233.002-.002.006-.004a12.436 12.436 0 00.073-.066 2.969 2.969 0 00.639-.861c.137-.287.235-.64.201-1.03-.034-.395-.2-.806-.554-1.21l-.452.395c.279.318.386.612.408.866a1.39 1.39 0 01-.145.72 2.287 2.287 0 01-.556.726l-.002.002.19.232zm1.49-3.528c.32.45.375.854.3 1.211-.079.37-.303.722-.592 1.035a5.084 5.084 0 01-.888.745 5.698 5.698 0 01-.417.255l-.024.013-.005.002h-.001l.137.268.137.267.001-.001.003-.001a5.685 5.685 0 001.498-1.14c.328-.356.629-.802.738-1.319.111-.53.014-1.104-.4-1.684l-.488.35zm-.175-.24l.174.24.488-.349-.176-.243-.486.352zm3.545-6.355c-1.371.79-2.366 1.453-3.064 2.034-.696.577-1.12 1.093-1.318 1.595-.204.519-.15.99.036 1.439.179.43.488.854.801 1.287l.486-.352c-.325-.45-.587-.813-.733-1.166-.14-.335-.168-.642-.031-.99.143-.363.479-.8 1.142-1.352.66-.549 1.622-1.192 2.98-1.975l-.299-.52zm-4.303 7.183c-1.026-1.175-1.214-2.133-1.01-2.905.212-.794.86-1.479 1.69-2.047.823-.564 1.783-.985 2.544-1.266a15.575 15.575 0 011.296-.413h.004l.001-.001-.072-.291-.073-.291h-.002l-.005.002a3.097 3.097 0 00-.098.025 16.165 16.165 0 00-1.258.406c-.784.29-1.796.73-2.677 1.334-.875.6-1.664 1.388-1.93 2.388-.27 1.023.026 2.18 1.138 3.454l.452-.395zm-4.13 8.35c-.417-.048-.627-.116-.72-.168-.045-.024-.041-.034-.03-.015a.124.124 0 01.013.083c-.005.02-.003-.003.057-.054a.704.704 0 01.082-.06l.004-.002-.151-.26-.15-.26v.001h-.001l-.002.001-.004.003a1.94 1.94 0 00-.05.032c-.031.02-.073.05-.117.089-.074.063-.215.197-.255.385a.477.477 0 00.054.342.658.658 0 00.258.24c.2.11.507.189.945.238l.068-.596zm5.328-.225c-2.256.424-3.285.456-5.327.224l-.068.596c2.105.24 3.194.204 5.506-.23l-.11-.59zm1.604.713a9.737 9.737 0 01-1.367-.659c-.008-.005-.014-.009-.018-.01l-.004-.003-.001-.001-.158.255-.159.255h.001l.002.001.006.004.023.014.084.05a10.362 10.362 0 001.375.654l.216-.56zm-7.757-1.253c-.517.144-.905.316-1.152.523a.919.919 0 00-.284.379.665.665 0 00-.001.46c.098.276.358.488.648.649.302.168.696.313 1.15.428 1.81.457 4.777.49 7.406-.63l-.235-.552c-2.494 1.061-5.324 1.03-7.023.6a4.304 4.304 0 01-1.007-.37c-.256-.143-.352-.263-.374-.326a.066.066 0 01-.001-.051.335.335 0 01.106-.127c.149-.125.438-.269.927-.404l-.16-.579zm.076-1.854c-.415-.043-.597-.121-.665-.172-.028-.021-.024-.027-.02-.014.004.012 0 .015.004.001a.509.509 0 01.125-.176 1.176 1.176 0 01.106-.096l.005-.004h.001l-.178-.242-.178-.241h-.001l-.002.001-.004.003-.012.01a1.51 1.51 0 00-.166.15c-.088.088-.218.24-.272.428-.029.1-.04.22 0 .346a.63.63 0 00.231.313c.203.153.523.244.965.29l.061-.597zm6.904-.33c-2.996.573-4.715.554-6.904.33l-.061.596c2.24.23 4.018.248 7.077-.337l-.113-.589zm1.23.664a2.835 2.835 0 01-.96-.579l-.002-.002h.001l-.213.212a46.433 46.433 0 00-.213.211v.001l.003.002.005.005.018.018.065.058a3.438 3.438 0 001.098.64l.199-.566zm-8.85-1.322c-.566.187-.984.386-1.25.603-.265.216-.45.517-.325.86.104.287.394.487.703.629.327.15.756.275 1.255.37 1.993.382 5.313.343 8.452-.569l-.167-.576c-3.052.887-6.276.92-8.172.556-.473-.09-.85-.203-1.117-.326-.284-.131-.374-.243-.39-.288-.003-.009-.005-.016.003-.036a.457.457 0 01.137-.155c.18-.147.516-.319 1.059-.498l-.188-.57zm12.144 5.238l-.19.232h-.001l-.002-.001v-.001c-.001 0-.001 0 0 0l.008.008c.008.008.02.021.03.037.025.035.031.06.03.074 0 .001.002.047-.098.129-.106.087-.309.198-.679.31l.173.574c.408-.123.695-.263.888-.42.198-.164.307-.358.316-.567a.722.722 0 00-.139-.445.907.907 0 00-.127-.145l-.012-.01-.004-.004-.002-.002-.191.231zM2.264 25.484c5.253.846 10.045.657 13.194.1 1.564-.278 2.76-.652 3.4-1.058.163-.104.305-.218.407-.345a.724.724 0 00.177-.47c-.008-.372-.334-.613-.681-.77l-.246.548c.15.068.24.13.287.178.023.023.033.04.037.048l.003.008v.005a.26.26 0 01-.044.076c-.047.059-.13.132-.261.215-.535.34-1.632.699-3.183.973-3.081.546-7.806.735-12.995-.1l-.095.592zm3.1-2.587c-.202-.14-.475-.19-.74-.2a4.4 4.4 0 00-.91.077 7.598 7.598 0 00-1.92.618c-.28.137-.534.293-.725.46-.18.158-.36.376-.369.643-.01.302.193.518.447.66.255.141.626.25 1.117.329l.095-.593c-.466-.075-.756-.17-.92-.26a.411.411 0 01-.13-.102l-.009-.013c0-.01.017-.083.164-.213.136-.12.34-.247.595-.372a7.003 7.003 0 011.759-.566c.295-.053.565-.076.784-.068.229.009.36.051.418.092l.344-.492zm-1.01.64c.271-.058.482-.081.621-.09a2.307 2.307 0 01.197-.005l.02-.299.02-.3h-.024a2.871 2.871 0 00-.25.005 4.88 4.88 0 00-.711.103l.126.586zm-1.313.513c-.097-.042-.115-.069-.11-.061.02.027.03.078.015.119-.006.017-.006.002.044-.039.045-.037.112-.08.2-.126.356-.188.903-.35 1.163-.406l-.126-.586c-.29.062-.894.239-1.317.461-.107.057-.212.121-.3.193a.715.715 0 00-.226.293.464.464 0 00.066.45.85.85 0 00.353.253l.238-.55zm14.695-.047c-1.434.431-4.473.721-7.502.76-1.508.018-3.002-.026-4.276-.143-1.285-.119-2.315-.31-2.917-.57l-.238.55c.696.302 1.809.498 3.1.617 1.3.12 2.816.164 4.339.145 3.033-.038 6.146-.327 7.667-.785l-.173-.574zM7.695 15.314l-.07-.292h-.003c-.002.002-.006.002-.01.003l-.041.01a16.032 16.032 0 00-.652.172c-.401.112-.913.27-1.332.442-.208.086-.406.18-.559.282-.076.051-.152.11-.213.18a.521.521 0 00-.135.297.45.45 0 00.128.35c.076.08.176.137.276.18.202.086.497.152.888.204l.079-.595c-.377-.05-.606-.108-.732-.162-.063-.027-.079-.043-.075-.04.01.012.039.053.034.114-.004.047-.026.064-.011.047a.495.495 0 01.094-.075c.104-.07.26-.147.455-.227.386-.16.87-.309 1.265-.42a20.51 20.51 0 01.632-.166l.038-.01.01-.001h.002v-.001l-.068-.292zm-3.987 1.237a9.68 9.68 0 012.822-.866c.36-.05.65-.068.849-.074a4.554 4.554 0 01.28.002h.016l.02-.299.02-.3h-.001-.027a3.501 3.501 0 00-.324-.002 8.124 8.124 0 00-.917.08c-.77.108-1.83.357-2.998.919l.26.54zm11.265.056c-2.373.62-5.878.79-8.46.64-1.3-.075-2.323-.23-2.849-.428a.984.984 0 01-.252-.128c-.045-.036-.014-.03-.011.023.003.054-.029.062.018.017.045-.044.134-.105.289-.18l-.26-.54c-.181.087-.334.18-.445.287a.581.581 0 00-.201.448c.01.19.126.327.236.414.112.09.257.16.414.22.619.235 1.725.39 3.026.466 2.617.151 6.19-.017 8.647-.659l-.152-.58zm1.271-.346l-.117-.276h-.001l-.002.001a7.207 7.207 0 00-1.243.662l.336.497c.234-.158.52-.31.75-.424a9.775 9.775 0 01.367-.172l.021-.009.006-.002-.117-.277zm-3.918.815a45.615 45.615 0 002.728-.322 52.192 52.192 0 001.152-.182l.067-.011.018-.003.004-.001h.001l-.052-.296-.052-.295h-.002-.004c-.003.002-.009.002-.016.004a13.238 13.238 0 01-.314.053c-.214.035-.52.084-.889.137a45.05 45.05 0 01-2.69.318l.05.598zm-6.354.066c1.33.177 3.941.135 6.354-.066l-.05-.598c-2.404.2-4.962.237-6.225.07l-.08.594zm10.39 3.177c2.47-1.276 3.309-2.614 3.12-3.712-.184-1.077-1.331-1.684-2.264-1.49l.122.587c.652-.135 1.432.312 1.551 1.005.115.671-.366 1.817-2.804 3.076l.275.534zm-.027.077a.91.91 0 00.066-.07.584.584 0 00.104-.168l-.561-.212a.147.147 0 01.007-.016l.002-.003-.008.01a.326.326 0 01-.024.024l.414.435zm.005-.005l-.424-.425.424.425zm-.004.004l.002-.001-.419-.43-.002.001.419.43zm.9-4.873c1.441-.503 2.593.258 2.732 1.18.07.463-.093 1.038-.687 1.615-.597.58-1.622 1.153-3.23 1.573l.151.58c1.669-.435 2.8-1.046 3.497-1.723.701-.681.968-1.44.863-2.135-.21-1.394-1.83-2.248-3.524-1.656l.198.566zm-.518.038l.253.162-.001.001v.001l-.001.001v-.002l.011-.014a.594.594 0 01.257-.187l-.2-.566a1.169 1.169 0 00-.566.434l-.003.005-.001.002h-.001v.001l.252.162zm.5-.444a5.432 5.432 0 00-.566.149 1.725 1.725 0 00-.04.015h-.003l-.002.001.111.28.112.278h-.001l.003-.001.018-.007a4.842 4.842 0 01.49-.127l-.122-.588zm-9.06 12.102c2.37.151 5.38.11 7.825-.25 1.22-.18 2.32-.441 3.133-.809.793-.358 1.422-.868 1.479-1.599l-.599-.046c-.029.377-.368.756-1.127 1.099-.739.333-1.775.585-2.974.761-2.393.353-5.358.395-7.698.246l-.038.598zm-3.979-.993a.622.622 0 00.105.228l.004.003a.41.41 0 00.004.004l.006.005a.385.385 0 00.055.037c.033.02.079.046.14.075.123.058.312.132.594.21.564.156 1.51.332 3.071.431l.039-.598c-1.535-.098-2.438-.27-2.95-.411a3.156 3.156 0 01-.497-.174.819.819 0 01-.081-.043l-.008-.005.003.002.003.003.004.002.003.004a.622.622 0 01.105.228h-.6zm12.168-.477c-3.985.746-8.91.659-11.82.181l-.097.592c2.974.488 7.97.576 12.027-.183l-.11-.59zm3.948-1.21l-.279-.111v-.001l.002-.002v-.003l.003-.006a.173.173 0 01.004-.007l-.001.002a.426.426 0 01-.05.06c-.063.064-.19.173-.434.308-.49.272-1.428.64-3.193.97l.11.59c1.8-.336 2.808-.72 3.374-1.035.284-.158.462-.301.573-.415a1.027 1.027 0 00.153-.203.499.499 0 00.015-.03l.001-.005.001-.001v-.001l-.279-.11z"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                Online Java Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/c-programming/online-compiler/" class="change-lang-row c " title="C Online Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 28" class="change-lang-btn-icon svg replaced-svg">
  <path fill-opacity=".4" d="M23.903 6.916l.067-.044c-.134-.243-.334-.464-.534-.574L12.696.155C12.518.045 12.274 0 12.007 0c-.267 0-.511.066-.69.155L.646 6.32C.267 6.54 0 7.093 0 7.513v12.308c0 .243.044.508.2.752l-.044.022c.11.176.266.331.422.42l10.718 6.165c.178.11.422.154.689.154.267 0 .511-.066.69-.154l10.672-6.165c.378-.221.645-.774.645-1.194V7.491c.022-.177 0-.376-.089-.575zM12.007 19.07a5.455 5.455 0 004.736-2.74l2.869 1.68a8.794 8.794 0 01-7.605 4.374c-4.847 0-8.783-3.91-8.783-8.728 0-4.817 3.936-8.728 8.783-8.728a8.796 8.796 0 017.627 4.42l-2.89 1.656a5.43 5.43 0 00-4.737-2.762c-3.002 0-5.448 2.431-5.448 5.414 0 2.983 2.446 5.414 5.448 5.414z"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                C Online Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/cpp-programming/online-compiler/" class="change-lang-row cpp active" title="C++ Online Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 27" class="change-lang-btn-icon svg replaced-svg">
  <path fill="#25265E" fill-opacity=".4" d="M23.903 6.639l.067-.043c-.134-.233-.334-.445-.534-.551L12.696.148C12.518.042 12.274 0 12.007 0a1.64 1.64 0 00-.69.148L.646 6.066C.267 6.278 0 6.808 0 7.21v11.814c0 .233.044.488.2.72l-.044.022c.11.17.266.318.422.403l10.718 5.918c.178.106.422.148.689.148.267 0 .511-.064.69-.148l10.672-5.918c.378-.212.645-.742.645-1.145V7.19c.022-.17 0-.36-.089-.551zm-7.893 6.893v-.849h1.111v-1.06h1.112v1.06h1.112v.849h-1.112v1.06h-1.112v-1.06H16.01zm.733-2.97c-.934-1.59-2.712-2.65-4.736-2.65-3.002 0-5.448 2.332-5.448 5.195 0 2.864 2.446 5.197 5.448 5.197 2.024 0 3.802-1.06 4.736-2.63l2.869 1.612c-1.512 2.502-4.358 4.2-7.605 4.2-4.847 0-8.783-3.755-8.783-8.379 0-4.623 3.936-8.377 8.783-8.377 3.269 0 6.115 1.718 7.627 4.242l-2.89 1.59zm6.604 2.97h-1.112v1.06h-.889v-1.06h-1.334v-.849h1.334v-1.06h.89v1.06h1.111v.849z"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                C++ Online Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/csharp-programming/online-compiler/" class="change-lang-row csharp " title="C# Online Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 28" class="change-lang-btn-icon svg replaced-svg">
  <path fill-opacity=".4" d="M23.903 6.916l.067-.044c-.134-.243-.334-.464-.534-.574L12.696.155C12.518.045 12.274 0 12.007 0c-.267 0-.511.066-.69.155L.646 6.32C.267 6.54 0 7.093 0 7.513v12.308c0 .243.044.508.2.752l-.044.022c.11.176.266.331.422.42l10.718 6.165c.178.11.422.154.689.154.267 0 .511-.066.69-.154l10.672-6.165c.378-.221.645-.774.645-1.194V7.491c.022-.177 0-.376-.089-.575zM12.007 22.384c-4.847 0-8.783-3.91-8.783-8.728 0-4.817 3.936-8.728 8.783-8.728a8.796 8.796 0 017.627 4.42l-2.89 1.656a5.43 5.43 0 00-4.737-2.762c-3.002 0-5.448 2.431-5.448 5.414 0 2.983 2.446 5.414 5.448 5.414a5.455 5.455 0 004.736-2.74l2.869 1.68a8.794 8.794 0 01-7.605 4.374zm11.34-9.17h-.711l-.2.884h.911v1.105h-1.112l-.266 1.326h-1.09l.267-1.326H20.3l-.267 1.326h-1.067l.267-1.326h-.556v-1.105h.778l.2-.884h-.978V12.11h1.178l.267-1.325h1.09l-.267 1.325h.845l.267-1.325h1.067l-.267 1.325h.49v1.105zm-2.824.884h.845l.2-.884h-.845l-.2.884z"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                C# Online Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/javascript/online-compiler/" class="change-lang-row javascript " title="JavaScript Online Compiler (Editor)">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 630 630" class="change-lang-btn-icon svg replaced-svg">
<rect width="630" height="630" fill="#25265E" fill-opacity="0.0"></rect>
<path d="m423.2 492.19c12.69 20.72 29.2 35.95 58.4 35.95 24.53 0 40.2-12.26 40.2-29.2 0-20.3-16.1-27.49-43.1-39.3l-14.8-6.35c-42.72-18.2-71.1-41-71.1-89.2 0-44.4 33.83-78.2 86.7-78.2 37.64 0 64.7 13.1 84.2 47.4l-46.1 29.6c-10.15-18.2-21.1-25.37-38.1-25.37-17.34 0-28.33 11-28.33 25.37 0 17.76 11 24.95 36.4 35.95l14.8 6.34c50.3 21.57 78.7 43.56 78.7 93 0 53.3-41.87 82.5-98.1 82.5-54.98 0-90.5-26.2-107.88-60.54zm-209.13 5.13c9.3 16.5 17.76 30.45 38.1 30.45 19.45 0 31.72-7.61 31.72-37.2v-201.3h59.2v202.1c0 61.3-35.94 89.2-88.4 89.2-47.4 0-74.85-24.53-88.81-54.075z"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                JavaScript Online Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/golang/online-compiler/" class="change-lang-row golang " title="Online GoLang Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<g clip-path="url(#clip0_2886_601)">
<path d="M3.00684 16.739C2.9516 16.739 2.89634 16.6837 2.9516 16.6285L3.33841 16.0759C3.39365 16.0206 3.44891 15.9654 3.55944 15.9654H10.522C10.5772 15.9654 10.6325 16.0206 10.5772 16.0759L10.2457 16.5731C10.1905 16.6285 10.1352 16.6837 10.0247 16.6837L3.00684 16.739ZM0.0781503 18.5072C0.0228897 18.5072 -0.0323709 18.4519 0.0228897 18.3967L0.409701 17.8441C0.464961 17.7888 0.520209 17.7336 0.63073 17.7336H9.52736C9.58262 17.7336 9.63788 17.7888 9.63788 17.8441L9.47211 18.3967C9.47211 18.4519 9.36159 18.5072 9.30633 18.5072H0.0781503ZM4.77513 20.3307C4.71987 20.3307 4.66461 20.2755 4.71987 20.2202L4.99616 19.7229C5.05142 19.6676 5.10668 19.6124 5.21719 19.6124H9.0853C9.14055 19.6124 9.19581 19.6676 9.19581 19.7229L9.14055 20.165C9.14055 20.2202 9.0853 20.2755 9.03004 20.2755L4.77513 20.3307ZM24.9997 16.3521L21.7394 17.181C21.4632 17.2362 21.408 17.2916 21.187 16.96C20.9106 16.6285 20.6896 16.4074 20.2475 16.2416C19.0318 15.6338 17.8161 15.7995 16.711 16.5179C15.3848 17.3468 14.7217 18.6178 14.7217 20.2202C14.7217 21.7674 15.8268 23.0384 17.3741 23.2595C18.7003 23.4252 19.8054 22.9831 20.6896 21.9886C20.8554 21.7674 21.0211 21.5464 21.2422 21.2702H17.4846C17.0977 21.2702 16.9872 20.9938 17.0977 20.6624C17.3741 20.0545 17.8161 19.0598 18.0925 18.5624C18.1477 18.4519 18.3134 18.2309 18.5898 18.2309H25.6628C25.6076 18.7835 25.6076 19.2809 25.5523 19.8334C25.3313 21.215 24.834 22.5412 23.9499 23.6462C22.5684 25.4698 20.7449 26.6303 18.4239 26.9617C16.4899 27.2381 14.7217 26.8512 13.1744 25.6908C11.7377 24.5857 10.9088 23.149 10.6879 21.3807C10.4115 19.2809 11.0746 17.3468 12.3455 15.689C13.727 13.8655 15.5505 12.7051 17.8161 12.3183C19.6396 11.9867 21.408 12.2078 22.9552 13.2576C24.0051 13.9207 24.7235 14.8602 25.2208 16.0206C25.2761 16.2416 25.2208 16.2969 24.9997 16.3521Z" fill="#6D6D93"></path>
<path d="M31.4177 27.1297C29.6494 27.0745 28.0469 26.5771 26.6653 25.4168C25.505 24.4221 24.7867 23.1511 24.5655 21.6592C24.2341 19.4489 24.8419 17.5148 26.1681 15.8018C27.6048 13.9229 29.3179 12.9836 31.6387 12.5415C33.628 12.2099 35.5068 12.3758 37.1646 13.5361C38.7118 14.586 39.6511 16.0227 39.9275 17.9015C40.259 20.554 39.4854 22.6537 37.7171 24.4773C36.4461 25.8035 34.8437 26.5771 33.0754 26.964C32.4675 27.0745 31.9149 27.0745 31.4177 27.1297ZM36.0594 19.283C36.0594 19.0068 36.0594 18.841 36.0041 18.6199C35.6725 16.6858 33.9043 15.5808 32.0255 16.0227C30.202 16.4096 29.0415 17.5701 28.5994 19.3935C28.2679 20.8856 28.9863 22.4328 30.3677 23.0959C31.4177 23.538 32.5228 23.4827 33.5175 22.9854C35.1199 22.2118 35.9489 20.9408 36.0594 19.283Z" fill="#6D6D93"></path>
</g>
<defs>
<clippath id="clip0_2886_601">
<rect width="40" height="40" fill="white"></rect>
</clippath>
</defs>
</svg>
              </span>
              <span class="nav-menu-text">
                Online GoLang Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/php/online-compiler/" class="change-lang-row php " title="Online PHP Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path d="M3.83821 13.8008H9.6625C11.372 13.8151 12.6107 14.308 13.3788 15.2786C14.1468 16.2492 14.4002 17.5748 14.1394 19.2556C14.0381 20.0236 13.8134 20.7769 13.4657 21.5158C13.1323 22.2547 12.669 22.921 12.0748 23.5152C11.3503 24.2684 10.5753 24.7465 9.74943 24.9495C8.9236 25.1525 8.06865 25.2538 7.185 25.2538H4.57711L3.75128 29.3829H0.730469L3.83821 13.8008ZM6.3809 16.2783L5.07696 22.798C5.16389 22.8124 5.25082 22.8197 5.33775 22.8197C5.43903 22.8197 5.54072 22.8197 5.642 22.8197C7.03288 22.8341 8.19208 22.6967 9.11919 22.4068C10.0463 22.1026 10.6696 21.0451 10.9882 19.2339C11.249 17.7126 10.9882 16.8359 10.2058 16.6043C9.4378 16.3726 8.4746 16.2639 7.3154 16.2783C7.14154 16.2926 6.97506 16.3 6.81555 16.3C6.67081 16.3 6.51868 16.3 6.35917 16.3L6.3809 16.2783Z" fill="#25265E" fill-opacity="0.67"></path>
<path d="M17.5748 9.64844H20.5739L19.7263 13.7993H22.4211C23.8989 13.8284 24.9999 14.1327 25.7244 14.7121C26.4634 15.2915 26.6807 16.3929 26.3764 18.0154L24.9203 25.2523H21.8778L23.2687 18.3414C23.4134 17.6169 23.37 17.1027 23.1383 16.7984C22.9066 16.4942 22.4068 16.342 21.6387 16.342L19.2265 16.3203L17.4444 25.2523H14.4453L17.5748 9.64844Z" fill="#25265E" fill-opacity="0.67"></path>
<path d="M29.5999 13.8008H35.4242C37.1337 13.8151 38.3725 14.308 39.1405 15.2786C39.9085 16.2492 40.1619 17.5748 39.9011 19.2556C39.7998 20.0236 39.5751 20.7769 39.2274 21.5158C38.894 22.2547 38.4307 22.921 37.8365 23.5152C37.112 24.2684 36.337 24.7465 35.5111 24.9495C34.6853 25.1525 33.8304 25.2538 32.9467 25.2538H30.3388L29.513 29.3829H26.4922L29.5999 13.8008ZM32.1426 16.2783L30.8387 22.798C30.9256 22.8124 31.0125 22.8197 31.0995 22.8197C31.2007 22.8197 31.3024 22.8197 31.4037 22.8197C32.7946 22.8341 33.9538 22.6967 34.8809 22.4068C35.808 22.1026 36.4313 21.0451 36.7499 19.2339C37.0107 17.7126 36.7499 16.8359 35.9675 16.6043C35.1995 16.3726 34.2363 16.2639 33.0771 16.2783C32.9033 16.2926 32.7368 16.3 32.5773 16.3C32.4325 16.3 32.2804 16.3 32.1209 16.3L32.1426 16.2783Z" fill="#25265E" fill-opacity="0.67"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                Online PHP Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/swift/online-compiler/" class="change-lang-row swift " title="Online Swift Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M29.9196 33.8549C32.0265 33.0205 36.1973 31.7405 38.4533 35.8806C38.9712 36.8532 40.1207 31.7059 35.9618 26.8506L35.8873 26.7661C35.9081 26.6956 35.9286 26.6286 35.9487 26.5631C35.9889 26.4317 36.0272 26.3061 36.0638 26.1702C38.159 18.6894 33.1565 9.75527 24.7445 5C28.3777 9.66308 30.0412 15.2949 28.5857 20.25C28.4536 20.7083 28.2951 21.1588 28.1109 21.5995C27.9383 21.4841 27.7225 21.361 27.4439 21.2149C21.1601 17.3644 15.3113 12.871 9.99608 7.81009C13.1936 12.2165 16.7354 16.3731 20.5896 20.2423C17.8902 18.7855 10.3022 13.638 5.53115 9.5593C6.1325 10.4985 6.82774 11.3767 7.60662 12.181C11.5537 16.9401 16.8504 22.768 23.0888 27.2504C18.7062 29.7914 12.4836 29.9798 6.257 27.2504C4.73944 26.619 3.30917 25.8028 2 24.8209C4.81703 28.9559 8.83711 32.1663 13.539 34.0355C19.5694 36.4535 25.5607 36.2113 29.9196 33.8549Z" fill="#25265E" fill-opacity="0.67"></path>
</svg>
              </span>
              <span class="nav-menu-text">
                Online Swift Compiler
              </span>
            </a>
            <a target="_blank" href="https://www.programiz.com/rust/online-compiler/" class="change-lang-row rust " title="Online Rust Compiler">
              <span class="change-lang-btn">
                <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<g clip-path="url(#clip0_2886_605)">
<path fill-rule="evenodd" clip-rule="evenodd" d="M13.8839 2.84442L14.4084 2.68631L15.1505 0.663847C15.2559 0.46731 15.603 0.273265 15.9643 0.487312C16.1369 0.589616 16.7641 1.30652 17.1641 1.76388C17.2685 1.88336 17.3577 1.98513 17.419 2.05361H18.0516L19.129 0.167618C19.2712 -0.0427356 19.6845 -0.0686346 19.924 0.167618C20.0716 0.313238 20.3929 0.883897 20.6664 1.36934C20.8365 1.6714 20.9878 1.94045 21.0674 2.05361H21.7002L23.0602 0.523151C23.2474 0.335748 23.7311 0.346159 23.9339 0.741787C24.0241 0.917836 24.1409 1.26358 24.261 1.61915C24.4107 2.06265 24.5658 2.52141 24.6807 2.68514C24.8677 2.79683 25.0045 2.83134 25.2354 2.82004L26.8525 1.60471C27.0398 1.4173 27.596 1.5539 27.7135 1.90697C27.7613 2.05037 27.7923 2.37341 27.826 2.72628C27.8754 3.24222 27.931 3.82191 28.0541 3.99709C28.1741 4.11715 28.4858 4.32123 28.7737 4.17717C29.0617 4.03311 29.9347 3.61122 30.3351 3.41829C30.5515 3.36255 30.9609 3.33726 31.0997 3.70769V6.0165L31.4596 6.33811L33.3422 5.88792C33.4493 5.86421 33.6878 5.83122 33.7855 5.88792C33.8831 5.94446 34.079 6.15146 34.1646 6.24798C34.1882 6.28658 34.2134 6.46532 34.1261 6.87189C34.0386 7.27831 33.7984 8.13447 33.6892 8.51171L34.0233 8.9619L36.2913 8.88484C36.452 8.95764 36.6884 9.30023 36.6319 9.54721C36.5883 9.7375 36.2534 10.4298 35.9726 11.0103C35.8889 11.1831 35.8101 11.3462 35.7453 11.4829L35.9958 12.036L38.0905 12.3383C38.249 12.4048 38.5492 12.6355 38.4824 13.0264L37.2295 14.7949C37.2038 14.9386 37.1935 15.2555 37.3579 15.3739C37.5225 15.4921 38.7073 15.899 39.2792 16.0876C39.4055 16.1627 39.6506 16.3732 39.6198 16.615C39.5888 16.8568 39.5469 16.9473 39.5297 16.9623L37.9813 18.3772V18.9046C38.6516 19.3032 39.9924 20.1328 39.9924 20.2615C39.9924 20.291 39.9939 20.3274 39.9956 20.3675C40.003 20.5459 40.0137 20.8013 39.9089 20.8853C39.8061 20.9677 38.581 21.687 37.9813 22.0365V22.6282C38.5252 23.1083 39.612 24.0892 39.6069 24.1716C39.6053 24.1959 39.606 24.2307 39.6067 24.2719C39.6091 24.4049 39.6128 24.6049 39.549 24.7376C39.4822 24.8765 38.0561 25.3871 37.3516 25.6251L37.2231 26.1975C37.6301 26.7419 38.4478 27.8425 38.4631 27.8888C38.4824 27.9467 38.5081 28.4548 38.174 28.6863L36.0537 28.9821L35.7838 29.4645L36.6641 31.4324C36.6983 31.5782 36.6757 31.9211 36.3106 32.1269L34.0167 32.0755L33.7149 32.4356L34.2032 34.6545C34.2009 34.7894 34.0656 35.0828 33.5413 35.1753L31.5174 34.6995L31.1126 34.9952L31.1768 37.2655C31.1211 37.424 30.8915 37.7195 30.4186 37.6321L28.5232 36.7381L28.0348 36.9954L27.6749 39.2076C27.5893 39.3319 27.3178 39.5497 26.9167 39.4263L25.1756 38.1786C25.0406 38.1916 24.7567 38.2327 24.7 38.2945C24.6435 38.3562 24.094 39.7864 23.8263 40.4939C23.6999 40.5817 23.3816 40.7138 23.1194 40.5389L21.6223 38.9568H21.1148L19.8619 40.9119C19.7612 40.9784 19.4982 41.0715 19.2514 40.9119L17.9663 38.9568H17.433L15.8587 40.6032C15.7367 40.646 15.4475 40.6856 15.2677 40.5003L14.3938 38.3651C14.3402 38.2966 14.1626 38.1659 13.8798 38.1916L12.0614 39.4906C11.8793 39.4991 11.4909 39.4468 11.3932 39.169C11.2956 38.8912 11.1427 37.6385 11.0784 37.0468L10.5515 36.7317L8.66886 37.6192C8.50183 37.6813 8.12144 37.7028 7.93648 37.2912V34.9888C7.92145 34.9373 7.82077 34.8075 7.53802 34.6995L5.48195 35.1817C5.30641 35.1883 4.94094 35.1007 4.8844 34.6995C4.82785 34.2981 5.17779 33.1217 5.35986 32.5836L5.07076 32.0948L2.7769 32.1527C2.62698 32.0605 2.33741 31.8041 2.37854 31.516C2.41966 31.2279 3.02536 30.0755 3.32307 29.5352L3.02108 29.0079L0.842888 28.6992C0.716532 28.6456 0.481784 28.4278 0.553747 27.9853L1.84522 26.1975C1.83237 26.0431 1.77584 25.7087 1.65246 25.6058L-0.300845 24.9434C-0.412213 24.8533 -0.623394 24.5948 -0.577139 24.2809C-0.53087 23.967 0.547293 23.0612 1.08058 22.6475V22.0365C0.476606 21.7278 -0.768624 21.0409 -0.917697 20.7631C-1.06676 20.4853 -0.979805 20.2743 -0.917697 20.2036L1.11917 18.943V18.3965C0.652268 18.0127 -0.335528 17.1526 -0.551416 16.7822V16.3513C-0.544992 16.3021 -0.460183 16.1712 -0.172317 16.0426C0.115533 15.914 1.23269 15.5517 1.75527 15.3866L1.87094 14.8272L0.579441 13.0457V12.602C0.624419 12.4969 0.818471 12.2816 1.23483 12.2611C1.6512 12.2406 2.62056 12.1067 3.0532 12.0424L3.31021 11.5086L2.38496 9.57289C2.34212 9.36072 2.36183 8.92466 2.78333 8.8783C3.20484 8.8321 4.44964 8.859 5.01935 8.8783L5.38552 8.53754L4.85229 6.36379C4.84801 6.1773 4.97437 5.80812 5.51414 5.82347L7.57021 6.31881L7.97505 5.9972L7.87863 3.72056C7.92357 3.56192 8.12918 3.25751 8.59187 3.30896L10.5002 4.24791L11.0721 3.96495L11.374 1.89411C11.4553 1.70332 11.7184 1.36547 12.1194 1.5404C12.5203 1.71532 13.4628 2.48263 13.8839 2.84442ZM20.7002 4.89056C20.7002 5.53728 20.1767 6.06134 19.5305 6.06134C18.8845 6.06134 18.3608 5.53728 18.3608 4.89056C18.3608 4.244 18.8845 3.71982 19.5305 3.71982C20.1767 3.71982 20.7002 4.244 20.7002 4.89056ZM24.5236 10.4094H8.48148C11.3531 7.29655 13.1362 6.23065 16.6696 5.7262C16.6696 5.7262 18.6748 7.73337 19.0091 7.90056C19.3433 8.0679 19.7703 8.10498 20.1788 7.90056C20.513 7.73337 22.3512 5.7262 22.3512 5.7262C27.0871 6.75866 29.3134 8.52402 32.7117 13.2527C32.3775 13.7546 31.6422 14.9588 31.3748 15.7616C31.1076 16.5644 31.4863 17.0997 31.709 17.2669L34.3827 18.605L34.5499 21.6156H32.5447C33.3802 25.2953 29.7038 25.4625 29.2026 22.9536C28.8835 21.3574 28.0884 20.5562 27.1972 19.7758C31.8762 17.2669 30.3723 11.2457 24.5236 10.4094ZM7.14457 17.2669C7.81303 16.8655 7.7573 16.3191 7.64599 16.0961L7.27076 15.1849C7.25269 15.1409 7.28504 15.0925 7.33257 15.0925H9.81838V24.7934H5.12585C4.3237 22.6525 4.45268 19.7955 4.61979 18.6246C5.17688 18.3459 6.47627 17.6683 7.14457 17.2669ZM16.3354 15.0925V17.7686H21.6827C23.6881 17.7686 24.0223 15.2599 21.6827 15.0925H16.3354ZM16.3354 24.7934V22.1173H20.513C21.5157 22.1173 22.6854 23.2881 23.0196 26.2987C23.287 28.7073 24.5793 29.4209 25.192 29.4766H31.709L30.3723 30.8146C30.0938 30.7588 29.236 30.614 28.0327 30.4801C26.8296 30.3463 26.4175 30.982 26.3617 31.3165L26.0275 34.1597C20.6881 35.8537 17.848 35.8704 12.9933 33.9926C12.9376 33.4351 12.7929 32.1193 12.6591 31.3165C12.5254 30.5135 11.935 30.3129 11.6565 30.3129L8.64867 30.8146L7.57583 29.5876C7.53802 29.5443 7.5687 29.4766 7.62625 29.4766H19.6775C19.7698 29.4766 19.8447 29.4017 19.8447 29.3093V24.9607C19.8447 24.8683 19.7698 24.7934 19.6775 24.7934H16.3354ZM34.3827 16.9324C35.0288 16.9324 35.5524 16.4082 35.5524 15.7616C35.5524 15.115 35.0288 14.5908 34.3827 14.5908C33.7367 14.5908 33.213 15.115 33.213 15.7616C33.213 16.4082 33.7367 16.9324 34.3827 16.9324ZM4.68672 16.8641C5.33268 16.8641 5.85641 16.3399 5.85641 15.6934C5.85641 15.0468 5.33268 14.5226 4.68672 14.5226C4.04068 14.5226 3.51697 15.0468 3.51697 15.6934C3.51697 16.3399 4.04068 16.8641 4.68672 16.8641ZM11.5203 33.1356C11.5203 33.7822 10.9966 34.3064 10.3506 34.3064C9.70449 34.3064 9.18091 33.7822 9.18091 33.1356C9.18091 32.4891 9.70449 31.9649 10.3506 31.9649C10.9966 31.9649 11.5203 32.4891 11.5203 33.1356ZM28.7012 34.3271C29.3471 34.3271 29.8709 33.8029 29.8709 33.1563C29.8709 32.5096 29.3471 31.9854 28.7012 31.9854C28.0552 31.9854 27.5314 32.5096 27.5314 33.1563C27.5314 33.8029 28.0552 34.3271 28.7012 34.3271Z" fill="#25265E" fill-opacity="0.67"></path>
</g>
<defs>
<clippath id="clip0_2886_605">
<rect width="40" height="40" fill="white"></rect>
</clippath>
</defs>
</svg>
              </span>
              <span class="nav-menu-text">
                Online Rust Compiler
              </span>
            </a>
          </div>
        </div>
      </div>

      <div class="wrapper" style="display: block;">
        <!-- <div class="mobile-view-banner">
          <div class="discount">
            <p style="width: 76px;">HOLIDAY SALE 50% OFF
          </div>
          <div class="banner-message">
            <p>Lifetime Deal! Pay once for skills that pay forever.</p>
            <a class="message-description--link-underlined" href="http://programiz.pro/offer/xmas-sale?utm_source=top-banner-button-compiler&utm_medium=button&utm_campaign=newyear-sale__top-banner-button__jan__50">
              <span>Claim Your Discount</span>
            </a>
          </div>
        </div>
        <div class="notice-bar-top d-none d-md-block">
          <div class="notice-bar-top__message">
            <div class="discount">
              <span class="sale-discount-first">60%</span>
              <span class="sale-discount-secondary">OFF</span>
            </div>
            <div class="message-description">
              <p id="banner-message">
                Black Friday | 60% off on Lifetime Deal! Pay once
                for skills that pay forever.
              </p>
              <a
                href="https://programiz.pro/offer/black-friday?utm_source=Banner-compiler&utm_medium=banner&utm_campaign=Black-Friday__Banner-compiler__November__60"
                class="message-description--link-underlined"
              >
                Claim Discount
              </a>
            </div>
          </div>
          <div class="sale-time-end">
            <p id="sale-time-countdown"></p>
          </div>
        </div> -->
        <div class="header">
          <div class="header-wrapper">
            <div class="burger-menu">
              <button type="button" class="burger-menu-btn" title="Open navigation">
                <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" class="svg burger-menu-btn-icon replaced-svg">
  <path d="M3 12H21" stroke="#25265E" stroke-opacity="0.7" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"></path>
  <path d="M3 6H21" stroke="#25265E" stroke-opacity="0.7" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"></path>
  <path d="M3 18H21" stroke="#25265E" stroke-opacity="0.7" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"></path>
</svg>
              </button>
            </div>
            <div class="logo-wrapper">
              <h1 class="logo-title-wrapper">
                <a href="https://www.programiz.com/" target="_blank" class="logo-link">
                  <img id="logo" src="./fibonacci_recurssion_files/logo.svg">
                  <span class="logo-sub-title-wrapper">
                    <span class="logo-sub-title">C++ Online Compiler</span>
                  </span>
                </a>
              </h1>
            </div>
          </div>
          <div class="compiler-header-ad">
            <div class="pgAdWrapper" style="min-width: 970px; min-height: 90px; display: flex; justify-content: center; align-items: center;"><div id="div-gpt-ad-Programizcom36786" class="content-top-ad" style="">
            <div id="google_ads_iframe_/8095840,68410703/.2_A.36786.3_Programiz.com_tier1_0__container__" style="border: 0pt none; width: 468px; height: 0px;"></div></div><div class="adSpinner ad-slot__label" style="width: 60px; height: 60px; text-align: center; line-height: 60px; margin: 10px auto; font-size: 12px; position: absolute;"><span style="color: rgb(243, 243, 243);">Ad</span></div></div>

            <!-- buysell ads -->
                <div class="compiler-header-ad" id="carbon-block"><script src="./fibonacci_recurssion_files/carbon.js.download" id="_carbonads_js"></script><div id="carbonads"><span><span class="carbon-wrap"><a href="https://srv.carbonads.net/ads/click/x/GTND42JYCAYD553EF6ALYKQNFTSD52QWCKBDVZ3JCYADK2QJCAADP5QKC6BI45QJF6SIE2JLCYBIK5QMCT7DP237HEYIK53UCTSIPKJECTNCYBZ52K?segment=placement:wwwprogramizcom;" class="carbon-img" target="_blank" rel="noopener sponsored"><img src="./fibonacci_recurssion_files/1670532337-Stock2.jpg" alt="ads via Carbon" border="0" height="100" width="130" style="max-width: 130px;"></a><a href="https://srv.carbonads.net/ads/click/x/GTND42JYCAYD553EF6ALYKQNFTSD52QWCKBDVZ3JCYADK2QJCAADP5QKC6BI45QJF6SIE2JLCYBIK5QMCT7DP237HEYIK53UCTSIPKJECTNCYBZ52K?segment=placement:wwwprogramizcom;" class="carbon-text" target="_blank" rel="noopener sponsored">Get 10 free Adobe Stock photos. Start downloading amazing royalty-free stock photos today.</a></span><a href="http://carbonads.net/?utm_source=wwwprogramizcom&amp;utm_medium=ad_via_link&amp;utm_campaign=in_unit&amp;utm_term=carbon" class="carbon-poweredby" target="_blank" rel="noopener sponsored">ads via Carbon</a></span></div></div>

          </div>
          <div id="add-replacement"></div>
          <div id="feedback-desktop">
            <a id="ad-link" href="https://programiz.pro/learn/master-cpp?utm_source=compiler-nav&amp;utm_campaign=programiz&amp;utm_medium=referral">C++ Certification ❯</a>
          </div>
          <div id="feedback-mobile">
            <a id="mobile-ad-link" href="https://programiz.pro/learn/master-cpp?utm_source=compiler-nav&amp;utm_campaign=programiz&amp;utm_medium=referral">C++ Course</a>
          </div>
        </div>
        <div class="mobile-top-bar clearfix">
          <div class="options-wrapper">
            <!-- <div id="back-button" class="options-item-wrapper clearfix">
              <img class="svg options-item" src="assets/icons/back-arrow.svg" />
            </div> -->
            <div id="toggle-dark-mode-mobile" class="options-item-wrapper clearfix">
              <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="toggle-dark-mode-mobile-icon moon svg options-item replaced-svg">
  <path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"></path>
</svg>
              <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="toggle-dark-mode-mobile-icon sun svg options-item replaced-svg">
  <circle cx="12" cy="12" r="5"></circle>
  <line x1="12" y1="1" x2="12" y2="3"></line>
  <line x1="12" y1="21" x2="12" y2="23"></line>
  <line x1="4.22" y1="4.22" x2="5.64" y2="5.64"></line>
  <line x1="18.36" y1="18.36" x2="19.78" y2="19.78"></line>
  <line x1="1" y1="12" x2="3" y2="12"></line>
  <line x1="21" y1="12" x2="23" y2="12"></line>
  <line x1="4.22" y1="19.78" x2="5.64" y2="18.36"></line>
  <line x1="18.36" y1="5.64" x2="19.78" y2="4.22"></line>
</svg>
            </div>
          </div>
          <div class="pills-wrapper">
            <div class="pills clearfix">
              <button class="pill active compiler-pill">
                main.cpp              </button>
              <button class="pill shell-pill">
                Output              </button>
            </div>
          </div>
          <div class="other-options-wrapper">
            <!-- <div id="feedback-mobile" class="options-item-wrapper">
              <a href="https://programiz.com/contact" class="options-item">
                <img class="svg" src="assets/icons/message-square.svg" />
              </a>
            </div> -->
            <div class="mobile-top-bar-run-button run"><img src="./fibonacci_recurssion_files/play.svg" alt="run-icon"></div>
          </div>
        </div>
        <div class="sidebar-wrapper">
          <a target="_blank" href="https://www.programiz.com/python-programming/online-compiler/" class="change-lang-btn python " title="Online Python Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 25" class="change-lang-btn-icon svg replaced-svg">
  <path fill-opacity=".4" d="M9.091 11.663h5.782c1.61 0 2.877-1.353 2.877-2.96V3.225c0-1.559-1.315-2.73-2.886-2.99A18.088 18.088 0 0011.853 0a16.25 16.25 0 00-2.738.235c-2.45.43-2.866 1.33-2.866 2.99v2.132H12v.788H4.025C2.342 6.145.868 7.152.408 9.064c-.532 2.191-.556 3.531 0 5.82.411 1.702 1.394 2.888 3.076 2.888h1.972V15.2c0-1.9 1.672-3.538 3.635-3.538zm-.364-7.707c-.6 0-1.087-.489-1.087-1.093 0-.606.486-1.1 1.087-1.1.597 0 1.086.494 1.086 1.1a1.09 1.09 0 01-1.086 1.093zm14.83 5.108c-.416-1.665-1.21-2.919-2.895-2.919h-2.118v2.558c0 1.98-1.744 3.551-3.671 3.551H9.091c-1.584 0-2.842 1.444-2.842 3.02v5.479c0 1.558 1.338 2.475 2.868 2.923 1.833.535 3.568.632 5.76 0 1.458-.42 2.873-1.264 2.873-2.923V18.56H12v-.788h8.662c1.682 0 2.31-1.138 2.895-2.89.604-1.801.578-3.506 0-5.818zm-8.32 10.958c.6 0 1.087.488 1.087 1.093 0 .606-.486 1.1-1.087 1.1a1.095 1.095 0 01-1.086-1.1 1.09 1.09 0 011.086-1.093z"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/r/online-compiler/" class="change-lang-btn r " title="Online R Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<g clip-path="url(#clip0_2886_601)">
<path fill-rule="evenodd" clip-rule="evenodd" d="M20.4449 31.25C31.1885 31.25 38.7187 25.3737 38.7187 18.125C38.7187 10.8763 32.1297 5 19.2656 5C8.52191 5 -0.1875 10.8763 -0.1875 18.125C-0.1875 25.3737 9.70118 31.25 20.4449 31.25ZM23.1934 27.9688C31.2187 27.9688 36.8437 23.9813 36.8437 19.0625C36.8437 14.1437 31.9219 10.1562 22.3125 10.1562C14.2871 10.1562 7.78131 14.1437 7.78131 19.0625C7.78131 23.9813 15.168 27.9688 23.1934 27.9688Z" fill="#6D6D93"></path>
<path fill-rule="evenodd" clip-rule="evenodd" d="M16.2188 35H22.7814V26.3281H24.2416C24.9302 26.3281 25.5635 26.7057 25.891 27.3116L30.047 35H37.547L32.9028 26.9784C32.572 26.4069 32.0506 25.9702 31.43 25.7445L29.8126 25.1562C32.3907 25.1562 35.2032 23.0469 35.4376 19.5312C35.672 16.0156 34.0314 13.2031 29.8126 13.2031H16.2188V35ZM27.0001 17.6562H22.7814V21.875H27.0001C29.3437 21.875 29.3437 17.6562 27.0001 17.6562Z" fill="#6D6D93"></path>
</g>
<defs>
<clippath id="clip0_2886_601">
<rect width="40" height="40" fill="white"></rect>
</clippath>
</defs>
</svg>
          </a>

          <a target="_blank" href="https://www.programiz.com/sql/online-compiler/" class="change-lang-btn sql" title="Online SQL Editor">
            <svg xmlns="http://www.w3.org/2000/svg" width="21" height="28" viewBox="0 0 21 28" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M10.8017 4.96503C16.2496 4.96503 20.6659 4.07743 20.6659 2.98251C20.6659 1.8876 16.2496 1 10.8017 1C5.35386 1 0.9375 1.8876 0.9375 2.98251C0.9375 4.07743 5.35386 4.96503 10.8017 4.96503ZM10.8019 4.19152C15.7423 4.19152 19.7474 3.58535 19.7474 2.8376C19.7474 2.08986 15.7423 1.48369 10.8019 1.48369C5.86141 1.48369 1.85638 2.08986 1.85638 2.8376C1.85638 3.58535 5.86141 4.19152 10.8019 4.19152Z" fill="#A8A8BF"></path>
<path d="M20.3659 2.98251C20.3659 3.01082 20.353 3.0721 20.2553 3.16803C20.1571 3.26451 19.9962 3.37195 19.762 3.48323C19.2951 3.70509 18.6003 3.91285 17.7177 4.09024C15.9573 4.44404 13.512 4.66503 10.8017 4.66503V5.26503C13.5393 5.26503 16.0261 5.04221 17.8359 4.67848C18.7383 4.49711 19.4881 4.27768 20.0195 4.02516C20.2845 3.89926 20.5112 3.75773 20.6757 3.59609C20.8409 3.4339 20.9659 3.22793 20.9659 2.98251H20.3659ZM10.8017 1.3C13.512 1.3 15.9573 1.52099 17.7177 1.87478C18.6003 2.05218 19.2951 2.25994 19.762 2.4818C19.9962 2.59307 20.1571 2.70052 20.2553 2.797C20.353 2.89292 20.3659 2.9542 20.3659 2.98251H20.9659C20.9659 2.7371 20.8409 2.53113 20.6757 2.36894C20.5112 2.2073 20.2845 2.06577 20.0195 1.93986C19.4881 1.68735 18.7383 1.46792 17.8359 1.28655C16.0261 0.922815 13.5393 0.7 10.8017 0.7V1.3ZM1.2375 2.98251C1.2375 2.9542 1.25046 2.89292 1.34812 2.797C1.44635 2.70052 1.60725 2.59307 1.84143 2.4818C2.30833 2.25994 3.00312 2.05218 3.88577 1.87478C5.64613 1.52099 8.09145 1.3 10.8017 1.3V0.7C8.06413 0.7 5.57733 0.922815 3.76755 1.28655C2.86513 1.46792 2.11534 1.68735 1.58392 1.93986C1.31896 2.06577 1.09226 2.2073 0.927691 2.36894C0.762556 2.53113 0.6375 2.7371 0.6375 2.98251H1.2375ZM10.8017 4.66503C8.09145 4.66503 5.64613 4.44404 3.88577 4.09024C3.00312 3.91285 2.30833 3.70509 1.84143 3.48323C1.60725 3.37195 1.44635 3.26451 1.34812 3.16803C1.25046 3.0721 1.2375 3.01082 1.2375 2.98251H0.6375C0.6375 3.22793 0.762556 3.4339 0.927691 3.59609C1.09226 3.75773 1.31896 3.89926 1.58392 4.02516C2.11534 4.27768 2.86513 4.49711 3.76755 4.67848C5.57733 5.04221 8.06413 5.26503 10.8017 5.26503V4.66503ZM19.4474 2.8376C19.4474 2.78735 19.4799 2.8007 19.3872 2.86927C19.3023 2.9321 19.158 3.00532 18.9433 3.08215C18.5175 3.2345 17.8846 3.37692 17.0824 3.49834C15.4825 3.74048 13.2619 3.89152 10.8019 3.89152V4.49152C13.2823 4.49152 15.5344 4.33947 17.1722 4.09159C17.9887 3.968 18.6659 3.81867 19.1454 3.64707C19.3834 3.56191 19.5906 3.46511 19.744 3.35166C19.8896 3.24396 20.0474 3.07479 20.0474 2.8376H19.4474ZM10.8019 1.78369C13.2619 1.78369 15.4825 1.93473 17.0824 2.17687C17.8846 2.29829 18.5175 2.4407 18.9433 2.59306C19.158 2.66989 19.3023 2.74311 19.3872 2.80594C19.4799 2.87451 19.4474 2.88785 19.4474 2.8376H20.0474C20.0474 2.60042 19.8896 2.43125 19.744 2.32355C19.5906 2.2101 19.3834 2.11329 19.1454 2.02814C18.6659 1.85654 17.9887 1.70721 17.1722 1.58362C15.5344 1.33574 13.2823 1.18369 10.8019 1.18369V1.78369ZM2.15638 2.8376C2.15638 2.88785 2.1238 2.87451 2.21651 2.80594C2.30145 2.74311 2.44574 2.66989 2.66043 2.59306C3.08621 2.4407 3.71909 2.29829 4.52134 2.17687C6.1212 1.93473 8.34185 1.78369 10.8019 1.78369V1.18369C8.32142 1.18369 6.06933 1.33574 4.43155 1.58362C3.61499 1.70721 2.93784 1.85654 2.45828 2.02814C2.22031 2.11329 2.0131 2.2101 1.85972 2.32355C1.71411 2.43125 1.55638 2.60042 1.55638 2.8376H2.15638ZM10.8019 3.89152C8.34185 3.89152 6.1212 3.74048 4.52134 3.49834C3.71909 3.37692 3.08621 3.2345 2.66043 3.08215C2.44574 3.00532 2.30145 2.9321 2.21651 2.86927C2.1238 2.8007 2.15638 2.78735 2.15638 2.8376H1.55638C1.55638 3.07479 1.71411 3.24396 1.85972 3.35166C2.0131 3.46511 2.22031 3.56191 2.45828 3.64707C2.93784 3.81867 3.61499 3.968 4.43155 4.09159C6.06933 4.33947 8.32142 4.49152 10.8019 4.49152V3.89152Z" fill="#A8A8BF"></path>
<path d="M0.9375 2.93359C0.9375 2.93359 4.43011 4.25786 10.7679 4.25786C17.1057 4.25786 20.6659 2.93359 20.6659 2.93359V8.76378C20.6659 8.76378 20.1582 11.1054 10.8017 11.1054C1.44522 11.1054 0.9375 8.76378 0.9375 8.76378V2.93359Z" fill="#A8A8BF" stroke="#A8A8BF" stroke-width="0.6" stroke-linecap="round" stroke-linejoin="round"></path>
<path d="M0.9375 11.0636C0.9375 11.0636 0.944635 10.9089 0.985854 10.8218C1.04301 10.7012 1.22762 10.5801 1.22762 10.5801C1.22762 10.5801 2.92001 12.3208 10.8017 12.3208C18.6834 12.3208 20.3033 10.5801 20.3033 10.5801C20.4998 10.6953 20.6196 10.8408 20.6659 11.0636V16.8938C20.6659 16.8938 20.1582 19.2354 10.8017 19.2354C1.44522 19.2354 0.9375 16.8938 0.9375 16.8938V11.0636Z" fill="#A8A8BF" stroke="#A8A8BF" stroke-width="0.6" stroke-linecap="round" stroke-linejoin="round"></path>
<path d="M0.9375 19.2238C0.9375 19.2238 0.944635 19.069 0.985854 18.982C1.04301 18.8613 1.22762 18.7402 1.22762 18.7402C1.22762 18.7402 2.92001 20.481 10.8017 20.481C18.6834 20.481 20.3033 18.7402 20.3033 18.7402C20.4998 18.8554 20.6196 19.0009 20.6659 19.2238V25.054C20.6659 25.054 20.1582 27.3956 10.8017 27.3956C1.44522 27.3956 0.9375 25.054 0.9375 25.054V19.2238Z" fill="#A8A8BF" stroke="#A8A8BF" stroke-width="0.6" stroke-linecap="round" stroke-linejoin="round"></path>
</svg>
          </a>

          <a target="_blank" href="https://www.programiz.com/html/online-compiler/" class="change-lang-btn html" title="Online HTML/CSS Editor">
            <svg xmlns="http://www.w3.org/2000/svg" width="86" height="98" viewBox="0 0 86 98" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M0 0L7.81641 87.668L42.8914 97.4047L78.0625 87.6547L85.8875 0H0ZM42.9624 39.9803H28.7717L27.7889 28.9693H42.9624H42.9998H68.9343L69.1499 26.5537L69.6405 21.1021L69.8976 18.2178H42.9998H42.9624H16.0381L16.2959 21.1021L18.9381 50.7326H42.9624H42.9998H56.2022L54.9546 64.6772L42.9624 67.9139V67.9149L42.9521 67.9178L30.9779 64.6834L30.2131 56.1092H19.4186L20.9248 72.9912L42.9506 79.1053L42.9998 79.092V79.0902L65.0054 72.9912L65.1671 71.1748L67.6936 42.8678L67.9554 39.9803H65.0585H42.9998H42.9624Z" fill="#F9F7F7"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/java-programming/online-compiler/" class="change-lang-btn java " title="Online Java Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 21 28" class="change-lang-btn-icon svg replaced-svg">
  <path fill-rule="evenodd" d="M13.266 1s2.718 2.703-2.578 6.857c-3.285 2.578-2.069 4.3-.902 5.951.343.485.68.963.9 1.456-2.48-2.223-4.298-4.18-3.078-6.002.596-.89 1.543-1.626 2.501-2.372 1.922-1.495 3.889-3.026 3.157-5.89zm-1.403 12.431c1.263 1.445-.331 2.744-.331 2.744s3.204-1.644 1.733-3.703a46.915 46.915 0 00-.175-.242c-1.278-1.764-2.008-2.772 3.452-5.92 0 0-8.956 2.223-4.679 7.122zm-4.65 7.678s-.998.577.713.772c2.073.236 3.133.202 5.417-.227 0 0 .601.374 1.44.698-5.122 2.18-11.592-.127-7.57-1.244zm-.625-2.847s-1.121.825.591 1.001c2.215.227 3.964.246 6.99-.333 0 0 .419.422 1.076.652-6.191 1.8-13.088.142-8.657-1.32zm11.235 6.028c1.554-.468.815-1.075.815-1.075 2.708 1.215-5.885 3.655-16.326 1.972-3.83-.617 1.842-2.77 2.88-2.044 0 0-.328-.022-.902.101-.55.118-2.3.678-1.368 1.082 2.597 1.122 11.945.854 14.9-.036zM6.01 16.845c-3.07-.409 1.684-1.531 1.684-1.531s-1.847-.124-4.117.967c-2.686 1.29 6.641 1.879 11.47.616.503-.34 1.196-.636 1.196-.636s-1.975.351-3.943.516c-2.409.2-4.993.24-6.29.067zM17.28 15.41c1.584-.328 3.854 2.108-1.055 4.642-.02.055-.084.115-.096.127l-.002.001c6.555-1.712 4.145-6.036 1.011-4.941a.89.89 0 00-.419.321s.174-.07.561-.15zm3.017 9.127c-.172 2.216-7.408 2.681-12.118 2.382-3.096-.198-3.699-.694-3.699-.694 2.941.483 7.902.57 11.923-.182 3.564-.666 3.893-1.506 3.893-1.506z" clip-rule="evenodd"></path>
  <path d="M10.688 7.857l-.186-.236.186.236zM13.266 1l.212-.213a.3.3 0 00-.502.287l.29-.074zm-3.48 12.808l-.245.174.245-.174zm.9 1.456l-.2.223a.3.3 0 00.474-.345l-.274.122zM7.608 9.262l-.25-.167.25.167zm2.501-2.372l.184.237-.184-.237zm1.423 9.285l-.19-.233a.3.3 0 00.327.5l-.137-.267zm.331-2.744l-.226.198.226-.197zm1.402-.96l.244-.174-.244.175zm-.175-.241l-.243.176.243-.176zm3.452-5.92l.15.26a.3.3 0 00-.222-.55l.072.29zM7.926 21.882l-.034.298.034-.298zm-.712-.773l.15.26a.3.3 0 00-.23-.549l.08.29zm6.129.546l.158-.255a.3.3 0 00-.214-.04l.056.295zm1.44.698l.118.276a.3.3 0 00-.01-.556l-.108.28zM7.18 19.263l-.03.298.03-.298zm-.591-1l.177.24a.3.3 0 00-.271-.526l.094.285zm7.582.667l.213-.211a.3.3 0 00-.27-.084l.057.295zm1.075.652l.084.288a.3.3 0 00.016-.571l-.1.283zm3.393 3.633l.122-.273a.3.3 0 00-.312.505l.19-.232zm-.815 1.075l.086.287-.086-.287zm-15.511.897l-.048.297.048-.297zm2.88-2.044l-.02.3a.3.3 0 00.192-.546l-.172.246zm-.902.101l.063.293-.063-.293zm-1.368 1.082l-.119.275.12-.275zm4.773-9.012l.069.292a.3.3 0 00-.049-.591l-.02.299zm-1.684 1.53l.04-.297-.04.297zm-2.433-.563l.13.27-.13-.27zm11.47.616l.077.29a.301.301 0 00.092-.042l-.168-.248zm1.196-.636l.118.276a.3.3 0 00-.17-.571l.052.295zm-3.943.516l.025.299-.025-.3zm3.923 3.275l-.137-.267a.3.3 0 00-.143.16l.28.107zm1.055-4.642l.061.294-.06-.294zm-1.15 4.769l-.208-.218-.005.005.212.213zm0 0l.208.215.003-.003-.212-.212zm-.003.001l-.209-.215a.3.3 0 00.285.506l-.076-.29zm1.011-4.941l-.099-.284.1.284zm-.419.321l-.252-.162a.3.3 0 00.364.44l-.112-.278zm-8.54 11.36l-.02.298.02-.299zm12.117-2.383l.3.023a.3.3 0 00-.579-.132l.28.11zM4.48 26.225l.049-.296a.3.3 0 00-.349.296h.3zm11.923-.182l-.055-.295.055.295zm-5.53-17.95c2.69-2.11 3.41-3.904 3.391-5.227-.01-.655-.2-1.17-.391-1.521a2.916 2.916 0 00-.353-.514 1.677 1.677 0 00-.036-.039L13.48.79h-.001V.787L13.265 1c-.211.213-.211.213-.212.212l.002.003.016.016c.014.017.037.042.064.078.055.07.131.178.208.32.154.286.311.706.32 1.246.015 1.067-.555 2.702-3.162 4.746l.37.473zm-.84 5.542c-.597-.844-1.13-1.613-1.165-2.467-.033-.82.397-1.812 2.006-3.075l-.37-.472c-1.677 1.316-2.28 2.473-2.235 3.571.043 1.064.703 1.982 1.273 2.79l.49-.347zm.928 1.507c-.233-.525-.59-1.028-.929-1.507l-.49.347c.347.49.666.944.871 1.404l.548-.244zM7.358 9.095c-.34.51-.475 1.04-.432 1.585.043.537.257 1.068.578 1.59.638 1.037 1.745 2.108 2.982 3.217l.4-.446c-1.242-1.114-2.285-2.133-2.871-3.086-.291-.473-.458-.912-.49-1.323-.033-.404.063-.801.332-1.203l-.499-.334zm2.567-2.442c-.948.738-1.938 1.505-2.567 2.442l.499.334c.564-.841 1.468-1.549 2.436-2.302l-.368-.474zm3.05-5.579c.343 1.342.056 2.352-.54 3.214-.609.882-1.54 1.61-2.51 2.365l.368.474c.953-.741 1.965-1.526 2.637-2.498.685-.993 1.016-2.18.627-3.703l-.582.148zm-1.443 15.1l.19.233.002-.002.006-.004a12.436 12.436 0 00.073-.066 2.969 2.969 0 00.639-.861c.137-.287.235-.64.201-1.03-.034-.395-.2-.806-.554-1.21l-.452.395c.279.318.386.612.408.866a1.39 1.39 0 01-.145.72 2.287 2.287 0 01-.556.726l-.002.002.19.232zm1.49-3.528c.32.45.375.854.3 1.211-.079.37-.303.722-.592 1.035a5.084 5.084 0 01-.888.745 5.698 5.698 0 01-.417.255l-.024.013-.005.002h-.001l.137.268.137.267.001-.001.003-.001a5.685 5.685 0 001.498-1.14c.328-.356.629-.802.738-1.319.111-.53.014-1.104-.4-1.684l-.488.35zm-.175-.24l.174.24.488-.349-.176-.243-.486.352zm3.545-6.355c-1.371.79-2.366 1.453-3.064 2.034-.696.577-1.12 1.093-1.318 1.595-.204.519-.15.99.036 1.439.179.43.488.854.801 1.287l.486-.352c-.325-.45-.587-.813-.733-1.166-.14-.335-.168-.642-.031-.99.143-.363.479-.8 1.142-1.352.66-.549 1.622-1.192 2.98-1.975l-.299-.52zm-4.303 7.183c-1.026-1.175-1.214-2.133-1.01-2.905.212-.794.86-1.479 1.69-2.047.823-.564 1.783-.985 2.544-1.266a15.575 15.575 0 011.296-.413h.004l.001-.001-.072-.291-.073-.291h-.002l-.005.002a3.097 3.097 0 00-.098.025 16.165 16.165 0 00-1.258.406c-.784.29-1.796.73-2.677 1.334-.875.6-1.664 1.388-1.93 2.388-.27 1.023.026 2.18 1.138 3.454l.452-.395zm-4.13 8.35c-.417-.048-.627-.116-.72-.168-.045-.024-.041-.034-.03-.015a.124.124 0 01.013.083c-.005.02-.003-.003.057-.054a.704.704 0 01.082-.06l.004-.002-.151-.26-.15-.26v.001h-.001l-.002.001-.004.003a1.94 1.94 0 00-.05.032c-.031.02-.073.05-.117.089-.074.063-.215.197-.255.385a.477.477 0 00.054.342.658.658 0 00.258.24c.2.11.507.189.945.238l.068-.596zm5.328-.225c-2.256.424-3.285.456-5.327.224l-.068.596c2.105.24 3.194.204 5.506-.23l-.11-.59zm1.604.713a9.737 9.737 0 01-1.367-.659c-.008-.005-.014-.009-.018-.01l-.004-.003-.001-.001-.158.255-.159.255h.001l.002.001.006.004.023.014.084.05a10.362 10.362 0 001.375.654l.216-.56zm-7.757-1.253c-.517.144-.905.316-1.152.523a.919.919 0 00-.284.379.665.665 0 00-.001.46c.098.276.358.488.648.649.302.168.696.313 1.15.428 1.81.457 4.777.49 7.406-.63l-.235-.552c-2.494 1.061-5.324 1.03-7.023.6a4.304 4.304 0 01-1.007-.37c-.256-.143-.352-.263-.374-.326a.066.066 0 01-.001-.051.335.335 0 01.106-.127c.149-.125.438-.269.927-.404l-.16-.579zm.076-1.854c-.415-.043-.597-.121-.665-.172-.028-.021-.024-.027-.02-.014.004.012 0 .015.004.001a.509.509 0 01.125-.176 1.176 1.176 0 01.106-.096l.005-.004h.001l-.178-.242-.178-.241h-.001l-.002.001-.004.003-.012.01a1.51 1.51 0 00-.166.15c-.088.088-.218.24-.272.428-.029.1-.04.22 0 .346a.63.63 0 00.231.313c.203.153.523.244.965.29l.061-.597zm6.904-.33c-2.996.573-4.715.554-6.904.33l-.061.596c2.24.23 4.018.248 7.077-.337l-.113-.589zm1.23.664a2.835 2.835 0 01-.96-.579l-.002-.002h.001l-.213.212a46.433 46.433 0 00-.213.211v.001l.003.002.005.005.018.018.065.058a3.438 3.438 0 001.098.64l.199-.566zm-8.85-1.322c-.566.187-.984.386-1.25.603-.265.216-.45.517-.325.86.104.287.394.487.703.629.327.15.756.275 1.255.37 1.993.382 5.313.343 8.452-.569l-.167-.576c-3.052.887-6.276.92-8.172.556-.473-.09-.85-.203-1.117-.326-.284-.131-.374-.243-.39-.288-.003-.009-.005-.016.003-.036a.457.457 0 01.137-.155c.18-.147.516-.319 1.059-.498l-.188-.57zm12.144 5.238l-.19.232h-.001l-.002-.001v-.001c-.001 0-.001 0 0 0l.008.008c.008.008.02.021.03.037.025.035.031.06.03.074 0 .001.002.047-.098.129-.106.087-.309.198-.679.31l.173.574c.408-.123.695-.263.888-.42.198-.164.307-.358.316-.567a.722.722 0 00-.139-.445.907.907 0 00-.127-.145l-.012-.01-.004-.004-.002-.002-.191.231zM2.264 25.484c5.253.846 10.045.657 13.194.1 1.564-.278 2.76-.652 3.4-1.058.163-.104.305-.218.407-.345a.724.724 0 00.177-.47c-.008-.372-.334-.613-.681-.77l-.246.548c.15.068.24.13.287.178.023.023.033.04.037.048l.003.008v.005a.26.26 0 01-.044.076c-.047.059-.13.132-.261.215-.535.34-1.632.699-3.183.973-3.081.546-7.806.735-12.995-.1l-.095.592zm3.1-2.587c-.202-.14-.475-.19-.74-.2a4.4 4.4 0 00-.91.077 7.598 7.598 0 00-1.92.618c-.28.137-.534.293-.725.46-.18.158-.36.376-.369.643-.01.302.193.518.447.66.255.141.626.25 1.117.329l.095-.593c-.466-.075-.756-.17-.92-.26a.411.411 0 01-.13-.102l-.009-.013c0-.01.017-.083.164-.213.136-.12.34-.247.595-.372a7.003 7.003 0 011.759-.566c.295-.053.565-.076.784-.068.229.009.36.051.418.092l.344-.492zm-1.01.64c.271-.058.482-.081.621-.09a2.307 2.307 0 01.197-.005l.02-.299.02-.3h-.024a2.871 2.871 0 00-.25.005 4.88 4.88 0 00-.711.103l.126.586zm-1.313.513c-.097-.042-.115-.069-.11-.061.02.027.03.078.015.119-.006.017-.006.002.044-.039.045-.037.112-.08.2-.126.356-.188.903-.35 1.163-.406l-.126-.586c-.29.062-.894.239-1.317.461-.107.057-.212.121-.3.193a.715.715 0 00-.226.293.464.464 0 00.066.45.85.85 0 00.353.253l.238-.55zm14.695-.047c-1.434.431-4.473.721-7.502.76-1.508.018-3.002-.026-4.276-.143-1.285-.119-2.315-.31-2.917-.57l-.238.55c.696.302 1.809.498 3.1.617 1.3.12 2.816.164 4.339.145 3.033-.038 6.146-.327 7.667-.785l-.173-.574zM7.695 15.314l-.07-.292h-.003c-.002.002-.006.002-.01.003l-.041.01a16.032 16.032 0 00-.652.172c-.401.112-.913.27-1.332.442-.208.086-.406.18-.559.282-.076.051-.152.11-.213.18a.521.521 0 00-.135.297.45.45 0 00.128.35c.076.08.176.137.276.18.202.086.497.152.888.204l.079-.595c-.377-.05-.606-.108-.732-.162-.063-.027-.079-.043-.075-.04.01.012.039.053.034.114-.004.047-.026.064-.011.047a.495.495 0 01.094-.075c.104-.07.26-.147.455-.227.386-.16.87-.309 1.265-.42a20.51 20.51 0 01.632-.166l.038-.01.01-.001h.002v-.001l-.068-.292zm-3.987 1.237a9.68 9.68 0 012.822-.866c.36-.05.65-.068.849-.074a4.554 4.554 0 01.28.002h.016l.02-.299.02-.3h-.001-.027a3.501 3.501 0 00-.324-.002 8.124 8.124 0 00-.917.08c-.77.108-1.83.357-2.998.919l.26.54zm11.265.056c-2.373.62-5.878.79-8.46.64-1.3-.075-2.323-.23-2.849-.428a.984.984 0 01-.252-.128c-.045-.036-.014-.03-.011.023.003.054-.029.062.018.017.045-.044.134-.105.289-.18l-.26-.54c-.181.087-.334.18-.445.287a.581.581 0 00-.201.448c.01.19.126.327.236.414.112.09.257.16.414.22.619.235 1.725.39 3.026.466 2.617.151 6.19-.017 8.647-.659l-.152-.58zm1.271-.346l-.117-.276h-.001l-.002.001a7.207 7.207 0 00-1.243.662l.336.497c.234-.158.52-.31.75-.424a9.775 9.775 0 01.367-.172l.021-.009.006-.002-.117-.277zm-3.918.815a45.615 45.615 0 002.728-.322 52.192 52.192 0 001.152-.182l.067-.011.018-.003.004-.001h.001l-.052-.296-.052-.295h-.002-.004c-.003.002-.009.002-.016.004a13.238 13.238 0 01-.314.053c-.214.035-.52.084-.889.137a45.05 45.05 0 01-2.69.318l.05.598zm-6.354.066c1.33.177 3.941.135 6.354-.066l-.05-.598c-2.404.2-4.962.237-6.225.07l-.08.594zm10.39 3.177c2.47-1.276 3.309-2.614 3.12-3.712-.184-1.077-1.331-1.684-2.264-1.49l.122.587c.652-.135 1.432.312 1.551 1.005.115.671-.366 1.817-2.804 3.076l.275.534zm-.027.077a.91.91 0 00.066-.07.584.584 0 00.104-.168l-.561-.212a.147.147 0 01.007-.016l.002-.003-.008.01a.326.326 0 01-.024.024l.414.435zm.005-.005l-.424-.425.424.425zm-.004.004l.002-.001-.419-.43-.002.001.419.43zm.9-4.873c1.441-.503 2.593.258 2.732 1.18.07.463-.093 1.038-.687 1.615-.597.58-1.622 1.153-3.23 1.573l.151.58c1.669-.435 2.8-1.046 3.497-1.723.701-.681.968-1.44.863-2.135-.21-1.394-1.83-2.248-3.524-1.656l.198.566zm-.518.038l.253.162-.001.001v.001l-.001.001v-.002l.011-.014a.594.594 0 01.257-.187l-.2-.566a1.169 1.169 0 00-.566.434l-.003.005-.001.002h-.001v.001l.252.162zm.5-.444a5.432 5.432 0 00-.566.149 1.725 1.725 0 00-.04.015h-.003l-.002.001.111.28.112.278h-.001l.003-.001.018-.007a4.842 4.842 0 01.49-.127l-.122-.588zm-9.06 12.102c2.37.151 5.38.11 7.825-.25 1.22-.18 2.32-.441 3.133-.809.793-.358 1.422-.868 1.479-1.599l-.599-.046c-.029.377-.368.756-1.127 1.099-.739.333-1.775.585-2.974.761-2.393.353-5.358.395-7.698.246l-.038.598zm-3.979-.993a.622.622 0 00.105.228l.004.003a.41.41 0 00.004.004l.006.005a.385.385 0 00.055.037c.033.02.079.046.14.075.123.058.312.132.594.21.564.156 1.51.332 3.071.431l.039-.598c-1.535-.098-2.438-.27-2.95-.411a3.156 3.156 0 01-.497-.174.819.819 0 01-.081-.043l-.008-.005.003.002.003.003.004.002.003.004a.622.622 0 01.105.228h-.6zm12.168-.477c-3.985.746-8.91.659-11.82.181l-.097.592c2.974.488 7.97.576 12.027-.183l-.11-.59zm3.948-1.21l-.279-.111v-.001l.002-.002v-.003l.003-.006a.173.173 0 01.004-.007l-.001.002a.426.426 0 01-.05.06c-.063.064-.19.173-.434.308-.49.272-1.428.64-3.193.97l.11.59c1.8-.336 2.808-.72 3.374-1.035.284-.158.462-.301.573-.415a1.027 1.027 0 00.153-.203.499.499 0 00.015-.03l.001-.005.001-.001v-.001l-.279-.11z"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/c-programming/online-compiler/" class="change-lang-btn c " title="Online C Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 28" class="change-lang-btn-icon svg replaced-svg">
  <path fill-opacity=".4" d="M23.903 6.916l.067-.044c-.134-.243-.334-.464-.534-.574L12.696.155C12.518.045 12.274 0 12.007 0c-.267 0-.511.066-.69.155L.646 6.32C.267 6.54 0 7.093 0 7.513v12.308c0 .243.044.508.2.752l-.044.022c.11.176.266.331.422.42l10.718 6.165c.178.11.422.154.689.154.267 0 .511-.066.69-.154l10.672-6.165c.378-.221.645-.774.645-1.194V7.491c.022-.177 0-.376-.089-.575zM12.007 19.07a5.455 5.455 0 004.736-2.74l2.869 1.68a8.794 8.794 0 01-7.605 4.374c-4.847 0-8.783-3.91-8.783-8.728 0-4.817 3.936-8.728 8.783-8.728a8.796 8.796 0 017.627 4.42l-2.89 1.656a5.43 5.43 0 00-4.737-2.762c-3.002 0-5.448 2.431-5.448 5.414 0 2.983 2.446 5.414 5.448 5.414z"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/cpp-programming/online-compiler/" class="change-lang-btn cpp active" title="Online C++ Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 27" class="change-lang-btn-icon svg replaced-svg">
  <path fill="#25265E" fill-opacity=".4" d="M23.903 6.639l.067-.043c-.134-.233-.334-.445-.534-.551L12.696.148C12.518.042 12.274 0 12.007 0a1.64 1.64 0 00-.69.148L.646 6.066C.267 6.278 0 6.808 0 7.21v11.814c0 .233.044.488.2.72l-.044.022c.11.17.266.318.422.403l10.718 5.918c.178.106.422.148.689.148.267 0 .511-.064.69-.148l10.672-5.918c.378-.212.645-.742.645-1.145V7.19c.022-.17 0-.36-.089-.551zm-7.893 6.893v-.849h1.111v-1.06h1.112v1.06h1.112v.849h-1.112v1.06h-1.112v-1.06H16.01zm.733-2.97c-.934-1.59-2.712-2.65-4.736-2.65-3.002 0-5.448 2.332-5.448 5.195 0 2.864 2.446 5.197 5.448 5.197 2.024 0 3.802-1.06 4.736-2.63l2.869 1.612c-1.512 2.502-4.358 4.2-7.605 4.2-4.847 0-8.783-3.755-8.783-8.379 0-4.623 3.936-8.377 8.783-8.377 3.269 0 6.115 1.718 7.627 4.242l-2.89 1.59zm6.604 2.97h-1.112v1.06h-.889v-1.06h-1.334v-.849h1.334v-1.06h.89v1.06h1.111v.849z"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/csharp-programming/online-compiler/" class="change-lang-btn csharp " title="Online C# Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 28" class="change-lang-btn-icon svg replaced-svg">
  <path fill-opacity=".4" d="M23.903 6.916l.067-.044c-.134-.243-.334-.464-.534-.574L12.696.155C12.518.045 12.274 0 12.007 0c-.267 0-.511.066-.69.155L.646 6.32C.267 6.54 0 7.093 0 7.513v12.308c0 .243.044.508.2.752l-.044.022c.11.176.266.331.422.42l10.718 6.165c.178.11.422.154.689.154.267 0 .511-.066.69-.154l10.672-6.165c.378-.221.645-.774.645-1.194V7.491c.022-.177 0-.376-.089-.575zM12.007 22.384c-4.847 0-8.783-3.91-8.783-8.728 0-4.817 3.936-8.728 8.783-8.728a8.796 8.796 0 017.627 4.42l-2.89 1.656a5.43 5.43 0 00-4.737-2.762c-3.002 0-5.448 2.431-5.448 5.414 0 2.983 2.446 5.414 5.448 5.414a5.455 5.455 0 004.736-2.74l2.869 1.68a8.794 8.794 0 01-7.605 4.374zm11.34-9.17h-.711l-.2.884h.911v1.105h-1.112l-.266 1.326h-1.09l.267-1.326H20.3l-.267 1.326h-1.067l.267-1.326h-.556v-1.105h.778l.2-.884h-.978V12.11h1.178l.267-1.325h1.09l-.267 1.325h.845l.267-1.325h1.067l-.267 1.325h.49v1.105zm-2.824.884h.845l.2-.884h-.845l-.2.884z"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/javascript/online-compiler/" class="change-lang-btn javascript " title="Online JavaScript Compiler (Editor)">
            <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 630 630" class="change-lang-btn-icon svg replaced-svg">
<rect width="630" height="630" fill="#25265E" fill-opacity="0.0"></rect>
<path d="m423.2 492.19c12.69 20.72 29.2 35.95 58.4 35.95 24.53 0 40.2-12.26 40.2-29.2 0-20.3-16.1-27.49-43.1-39.3l-14.8-6.35c-42.72-18.2-71.1-41-71.1-89.2 0-44.4 33.83-78.2 86.7-78.2 37.64 0 64.7 13.1 84.2 47.4l-46.1 29.6c-10.15-18.2-21.1-25.37-38.1-25.37-17.34 0-28.33 11-28.33 25.37 0 17.76 11 24.95 36.4 35.95l14.8 6.34c50.3 21.57 78.7 43.56 78.7 93 0 53.3-41.87 82.5-98.1 82.5-54.98 0-90.5-26.2-107.88-60.54zm-209.13 5.13c9.3 16.5 17.76 30.45 38.1 30.45 19.45 0 31.72-7.61 31.72-37.2v-201.3h59.2v202.1c0 61.3-35.94 89.2-88.4 89.2-47.4 0-74.85-24.53-88.81-54.075z"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/golang/online-compiler/" class="change-lang-btn golang " title="Online Golang Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<g clip-path="url(#clip0_2886_601)">
<path d="M3.00684 16.739C2.9516 16.739 2.89634 16.6837 2.9516 16.6285L3.33841 16.0759C3.39365 16.0206 3.44891 15.9654 3.55944 15.9654H10.522C10.5772 15.9654 10.6325 16.0206 10.5772 16.0759L10.2457 16.5731C10.1905 16.6285 10.1352 16.6837 10.0247 16.6837L3.00684 16.739ZM0.0781503 18.5072C0.0228897 18.5072 -0.0323709 18.4519 0.0228897 18.3967L0.409701 17.8441C0.464961 17.7888 0.520209 17.7336 0.63073 17.7336H9.52736C9.58262 17.7336 9.63788 17.7888 9.63788 17.8441L9.47211 18.3967C9.47211 18.4519 9.36159 18.5072 9.30633 18.5072H0.0781503ZM4.77513 20.3307C4.71987 20.3307 4.66461 20.2755 4.71987 20.2202L4.99616 19.7229C5.05142 19.6676 5.10668 19.6124 5.21719 19.6124H9.0853C9.14055 19.6124 9.19581 19.6676 9.19581 19.7229L9.14055 20.165C9.14055 20.2202 9.0853 20.2755 9.03004 20.2755L4.77513 20.3307ZM24.9997 16.3521L21.7394 17.181C21.4632 17.2362 21.408 17.2916 21.187 16.96C20.9106 16.6285 20.6896 16.4074 20.2475 16.2416C19.0318 15.6338 17.8161 15.7995 16.711 16.5179C15.3848 17.3468 14.7217 18.6178 14.7217 20.2202C14.7217 21.7674 15.8268 23.0384 17.3741 23.2595C18.7003 23.4252 19.8054 22.9831 20.6896 21.9886C20.8554 21.7674 21.0211 21.5464 21.2422 21.2702H17.4846C17.0977 21.2702 16.9872 20.9938 17.0977 20.6624C17.3741 20.0545 17.8161 19.0598 18.0925 18.5624C18.1477 18.4519 18.3134 18.2309 18.5898 18.2309H25.6628C25.6076 18.7835 25.6076 19.2809 25.5523 19.8334C25.3313 21.215 24.834 22.5412 23.9499 23.6462C22.5684 25.4698 20.7449 26.6303 18.4239 26.9617C16.4899 27.2381 14.7217 26.8512 13.1744 25.6908C11.7377 24.5857 10.9088 23.149 10.6879 21.3807C10.4115 19.2809 11.0746 17.3468 12.3455 15.689C13.727 13.8655 15.5505 12.7051 17.8161 12.3183C19.6396 11.9867 21.408 12.2078 22.9552 13.2576C24.0051 13.9207 24.7235 14.8602 25.2208 16.0206C25.2761 16.2416 25.2208 16.2969 24.9997 16.3521Z" fill="#6D6D93"></path>
<path d="M31.4177 27.1297C29.6494 27.0745 28.0469 26.5771 26.6653 25.4168C25.505 24.4221 24.7867 23.1511 24.5655 21.6592C24.2341 19.4489 24.8419 17.5148 26.1681 15.8018C27.6048 13.9229 29.3179 12.9836 31.6387 12.5415C33.628 12.2099 35.5068 12.3758 37.1646 13.5361C38.7118 14.586 39.6511 16.0227 39.9275 17.9015C40.259 20.554 39.4854 22.6537 37.7171 24.4773C36.4461 25.8035 34.8437 26.5771 33.0754 26.964C32.4675 27.0745 31.9149 27.0745 31.4177 27.1297ZM36.0594 19.283C36.0594 19.0068 36.0594 18.841 36.0041 18.6199C35.6725 16.6858 33.9043 15.5808 32.0255 16.0227C30.202 16.4096 29.0415 17.5701 28.5994 19.3935C28.2679 20.8856 28.9863 22.4328 30.3677 23.0959C31.4177 23.538 32.5228 23.4827 33.5175 22.9854C35.1199 22.2118 35.9489 20.9408 36.0594 19.283Z" fill="#6D6D93"></path>
</g>
<defs>
<clippath id="clip0_2886_601">
<rect width="40" height="40" fill="white"></rect>
</clippath>
</defs>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/php/online-compiler/" class="change-lang-btn php " title="Online PHP Compiler ">
            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path d="M3.83821 13.8008H9.6625C11.372 13.8151 12.6107 14.308 13.3788 15.2786C14.1468 16.2492 14.4002 17.5748 14.1394 19.2556C14.0381 20.0236 13.8134 20.7769 13.4657 21.5158C13.1323 22.2547 12.669 22.921 12.0748 23.5152C11.3503 24.2684 10.5753 24.7465 9.74943 24.9495C8.9236 25.1525 8.06865 25.2538 7.185 25.2538H4.57711L3.75128 29.3829H0.730469L3.83821 13.8008ZM6.3809 16.2783L5.07696 22.798C5.16389 22.8124 5.25082 22.8197 5.33775 22.8197C5.43903 22.8197 5.54072 22.8197 5.642 22.8197C7.03288 22.8341 8.19208 22.6967 9.11919 22.4068C10.0463 22.1026 10.6696 21.0451 10.9882 19.2339C11.249 17.7126 10.9882 16.8359 10.2058 16.6043C9.4378 16.3726 8.4746 16.2639 7.3154 16.2783C7.14154 16.2926 6.97506 16.3 6.81555 16.3C6.67081 16.3 6.51868 16.3 6.35917 16.3L6.3809 16.2783Z" fill="#25265E" fill-opacity="0.67"></path>
<path d="M17.5748 9.64844H20.5739L19.7263 13.7993H22.4211C23.8989 13.8284 24.9999 14.1327 25.7244 14.7121C26.4634 15.2915 26.6807 16.3929 26.3764 18.0154L24.9203 25.2523H21.8778L23.2687 18.3414C23.4134 17.6169 23.37 17.1027 23.1383 16.7984C22.9066 16.4942 22.4068 16.342 21.6387 16.342L19.2265 16.3203L17.4444 25.2523H14.4453L17.5748 9.64844Z" fill="#25265E" fill-opacity="0.67"></path>
<path d="M29.5999 13.8008H35.4242C37.1337 13.8151 38.3725 14.308 39.1405 15.2786C39.9085 16.2492 40.1619 17.5748 39.9011 19.2556C39.7998 20.0236 39.5751 20.7769 39.2274 21.5158C38.894 22.2547 38.4307 22.921 37.8365 23.5152C37.112 24.2684 36.337 24.7465 35.5111 24.9495C34.6853 25.1525 33.8304 25.2538 32.9467 25.2538H30.3388L29.513 29.3829H26.4922L29.5999 13.8008ZM32.1426 16.2783L30.8387 22.798C30.9256 22.8124 31.0125 22.8197 31.0995 22.8197C31.2007 22.8197 31.3024 22.8197 31.4037 22.8197C32.7946 22.8341 33.9538 22.6967 34.8809 22.4068C35.808 22.1026 36.4313 21.0451 36.7499 19.2339C37.0107 17.7126 36.7499 16.8359 35.9675 16.6043C35.1995 16.3726 34.2363 16.2639 33.0771 16.2783C32.9033 16.2926 32.7368 16.3 32.5773 16.3C32.4325 16.3 32.2804 16.3 32.1209 16.3L32.1426 16.2783Z" fill="#25265E" fill-opacity="0.67"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/swift/online-compiler/" class="change-lang-btn swift " title="Online Swift Compiler ">
            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<path fill-rule="evenodd" clip-rule="evenodd" d="M29.9196 33.8549C32.0265 33.0205 36.1973 31.7405 38.4533 35.8806C38.9712 36.8532 40.1207 31.7059 35.9618 26.8506L35.8873 26.7661C35.9081 26.6956 35.9286 26.6286 35.9487 26.5631C35.9889 26.4317 36.0272 26.3061 36.0638 26.1702C38.159 18.6894 33.1565 9.75527 24.7445 5C28.3777 9.66308 30.0412 15.2949 28.5857 20.25C28.4536 20.7083 28.2951 21.1588 28.1109 21.5995C27.9383 21.4841 27.7225 21.361 27.4439 21.2149C21.1601 17.3644 15.3113 12.871 9.99608 7.81009C13.1936 12.2165 16.7354 16.3731 20.5896 20.2423C17.8902 18.7855 10.3022 13.638 5.53115 9.5593C6.1325 10.4985 6.82774 11.3767 7.60662 12.181C11.5537 16.9401 16.8504 22.768 23.0888 27.2504C18.7062 29.7914 12.4836 29.9798 6.257 27.2504C4.73944 26.619 3.30917 25.8028 2 24.8209C4.81703 28.9559 8.83711 32.1663 13.539 34.0355C19.5694 36.4535 25.5607 36.2113 29.9196 33.8549Z" fill="#25265E" fill-opacity="0.67"></path>
</svg>
          </a>
          <a target="_blank" href="https://www.programiz.com/rust/online-compiler/" class="change-lang-btn rust " title="Online Rust Compiler">
            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" viewBox="0 0 40 40" fill="none" class="change-lang-btn-icon svg replaced-svg">
<g clip-path="url(#clip0_2886_605)">
<path fill-rule="evenodd" clip-rule="evenodd" d="M13.8839 2.84442L14.4084 2.68631L15.1505 0.663847C15.2559 0.46731 15.603 0.273265 15.9643 0.487312C16.1369 0.589616 16.7641 1.30652 17.1641 1.76388C17.2685 1.88336 17.3577 1.98513 17.419 2.05361H18.0516L19.129 0.167618C19.2712 -0.0427356 19.6845 -0.0686346 19.924 0.167618C20.0716 0.313238 20.3929 0.883897 20.6664 1.36934C20.8365 1.6714 20.9878 1.94045 21.0674 2.05361H21.7002L23.0602 0.523151C23.2474 0.335748 23.7311 0.346159 23.9339 0.741787C24.0241 0.917836 24.1409 1.26358 24.261 1.61915C24.4107 2.06265 24.5658 2.52141 24.6807 2.68514C24.8677 2.79683 25.0045 2.83134 25.2354 2.82004L26.8525 1.60471C27.0398 1.4173 27.596 1.5539 27.7135 1.90697C27.7613 2.05037 27.7923 2.37341 27.826 2.72628C27.8754 3.24222 27.931 3.82191 28.0541 3.99709C28.1741 4.11715 28.4858 4.32123 28.7737 4.17717C29.0617 4.03311 29.9347 3.61122 30.3351 3.41829C30.5515 3.36255 30.9609 3.33726 31.0997 3.70769V6.0165L31.4596 6.33811L33.3422 5.88792C33.4493 5.86421 33.6878 5.83122 33.7855 5.88792C33.8831 5.94446 34.079 6.15146 34.1646 6.24798C34.1882 6.28658 34.2134 6.46532 34.1261 6.87189C34.0386 7.27831 33.7984 8.13447 33.6892 8.51171L34.0233 8.9619L36.2913 8.88484C36.452 8.95764 36.6884 9.30023 36.6319 9.54721C36.5883 9.7375 36.2534 10.4298 35.9726 11.0103C35.8889 11.1831 35.8101 11.3462 35.7453 11.4829L35.9958 12.036L38.0905 12.3383C38.249 12.4048 38.5492 12.6355 38.4824 13.0264L37.2295 14.7949C37.2038 14.9386 37.1935 15.2555 37.3579 15.3739C37.5225 15.4921 38.7073 15.899 39.2792 16.0876C39.4055 16.1627 39.6506 16.3732 39.6198 16.615C39.5888 16.8568 39.5469 16.9473 39.5297 16.9623L37.9813 18.3772V18.9046C38.6516 19.3032 39.9924 20.1328 39.9924 20.2615C39.9924 20.291 39.9939 20.3274 39.9956 20.3675C40.003 20.5459 40.0137 20.8013 39.9089 20.8853C39.8061 20.9677 38.581 21.687 37.9813 22.0365V22.6282C38.5252 23.1083 39.612 24.0892 39.6069 24.1716C39.6053 24.1959 39.606 24.2307 39.6067 24.2719C39.6091 24.4049 39.6128 24.6049 39.549 24.7376C39.4822 24.8765 38.0561 25.3871 37.3516 25.6251L37.2231 26.1975C37.6301 26.7419 38.4478 27.8425 38.4631 27.8888C38.4824 27.9467 38.5081 28.4548 38.174 28.6863L36.0537 28.9821L35.7838 29.4645L36.6641 31.4324C36.6983 31.5782 36.6757 31.9211 36.3106 32.1269L34.0167 32.0755L33.7149 32.4356L34.2032 34.6545C34.2009 34.7894 34.0656 35.0828 33.5413 35.1753L31.5174 34.6995L31.1126 34.9952L31.1768 37.2655C31.1211 37.424 30.8915 37.7195 30.4186 37.6321L28.5232 36.7381L28.0348 36.9954L27.6749 39.2076C27.5893 39.3319 27.3178 39.5497 26.9167 39.4263L25.1756 38.1786C25.0406 38.1916 24.7567 38.2327 24.7 38.2945C24.6435 38.3562 24.094 39.7864 23.8263 40.4939C23.6999 40.5817 23.3816 40.7138 23.1194 40.5389L21.6223 38.9568H21.1148L19.8619 40.9119C19.7612 40.9784 19.4982 41.0715 19.2514 40.9119L17.9663 38.9568H17.433L15.8587 40.6032C15.7367 40.646 15.4475 40.6856 15.2677 40.5003L14.3938 38.3651C14.3402 38.2966 14.1626 38.1659 13.8798 38.1916L12.0614 39.4906C11.8793 39.4991 11.4909 39.4468 11.3932 39.169C11.2956 38.8912 11.1427 37.6385 11.0784 37.0468L10.5515 36.7317L8.66886 37.6192C8.50183 37.6813 8.12144 37.7028 7.93648 37.2912V34.9888C7.92145 34.9373 7.82077 34.8075 7.53802 34.6995L5.48195 35.1817C5.30641 35.1883 4.94094 35.1007 4.8844 34.6995C4.82785 34.2981 5.17779 33.1217 5.35986 32.5836L5.07076 32.0948L2.7769 32.1527C2.62698 32.0605 2.33741 31.8041 2.37854 31.516C2.41966 31.2279 3.02536 30.0755 3.32307 29.5352L3.02108 29.0079L0.842888 28.6992C0.716532 28.6456 0.481784 28.4278 0.553747 27.9853L1.84522 26.1975C1.83237 26.0431 1.77584 25.7087 1.65246 25.6058L-0.300845 24.9434C-0.412213 24.8533 -0.623394 24.5948 -0.577139 24.2809C-0.53087 23.967 0.547293 23.0612 1.08058 22.6475V22.0365C0.476606 21.7278 -0.768624 21.0409 -0.917697 20.7631C-1.06676 20.4853 -0.979805 20.2743 -0.917697 20.2036L1.11917 18.943V18.3965C0.652268 18.0127 -0.335528 17.1526 -0.551416 16.7822V16.3513C-0.544992 16.3021 -0.460183 16.1712 -0.172317 16.0426C0.115533 15.914 1.23269 15.5517 1.75527 15.3866L1.87094 14.8272L0.579441 13.0457V12.602C0.624419 12.4969 0.818471 12.2816 1.23483 12.2611C1.6512 12.2406 2.62056 12.1067 3.0532 12.0424L3.31021 11.5086L2.38496 9.57289C2.34212 9.36072 2.36183 8.92466 2.78333 8.8783C3.20484 8.8321 4.44964 8.859 5.01935 8.8783L5.38552 8.53754L4.85229 6.36379C4.84801 6.1773 4.97437 5.80812 5.51414 5.82347L7.57021 6.31881L7.97505 5.9972L7.87863 3.72056C7.92357 3.56192 8.12918 3.25751 8.59187 3.30896L10.5002 4.24791L11.0721 3.96495L11.374 1.89411C11.4553 1.70332 11.7184 1.36547 12.1194 1.5404C12.5203 1.71532 13.4628 2.48263 13.8839 2.84442ZM20.7002 4.89056C20.7002 5.53728 20.1767 6.06134 19.5305 6.06134C18.8845 6.06134 18.3608 5.53728 18.3608 4.89056C18.3608 4.244 18.8845 3.71982 19.5305 3.71982C20.1767 3.71982 20.7002 4.244 20.7002 4.89056ZM24.5236 10.4094H8.48148C11.3531 7.29655 13.1362 6.23065 16.6696 5.7262C16.6696 5.7262 18.6748 7.73337 19.0091 7.90056C19.3433 8.0679 19.7703 8.10498 20.1788 7.90056C20.513 7.73337 22.3512 5.7262 22.3512 5.7262C27.0871 6.75866 29.3134 8.52402 32.7117 13.2527C32.3775 13.7546 31.6422 14.9588 31.3748 15.7616C31.1076 16.5644 31.4863 17.0997 31.709 17.2669L34.3827 18.605L34.5499 21.6156H32.5447C33.3802 25.2953 29.7038 25.4625 29.2026 22.9536C28.8835 21.3574 28.0884 20.5562 27.1972 19.7758C31.8762 17.2669 30.3723 11.2457 24.5236 10.4094ZM7.14457 17.2669C7.81303 16.8655 7.7573 16.3191 7.64599 16.0961L7.27076 15.1849C7.25269 15.1409 7.28504 15.0925 7.33257 15.0925H9.81838V24.7934H5.12585C4.3237 22.6525 4.45268 19.7955 4.61979 18.6246C5.17688 18.3459 6.47627 17.6683 7.14457 17.2669ZM16.3354 15.0925V17.7686H21.6827C23.6881 17.7686 24.0223 15.2599 21.6827 15.0925H16.3354ZM16.3354 24.7934V22.1173H20.513C21.5157 22.1173 22.6854 23.2881 23.0196 26.2987C23.287 28.7073 24.5793 29.4209 25.192 29.4766H31.709L30.3723 30.8146C30.0938 30.7588 29.236 30.614 28.0327 30.4801C26.8296 30.3463 26.4175 30.982 26.3617 31.3165L26.0275 34.1597C20.6881 35.8537 17.848 35.8704 12.9933 33.9926C12.9376 33.4351 12.7929 32.1193 12.6591 31.3165C12.5254 30.5135 11.935 30.3129 11.6565 30.3129L8.64867 30.8146L7.57583 29.5876C7.53802 29.5443 7.5687 29.4766 7.62625 29.4766H19.6775C19.7698 29.4766 19.8447 29.4017 19.8447 29.3093V24.9607C19.8447 24.8683 19.7698 24.7934 19.6775 24.7934H16.3354ZM34.3827 16.9324C35.0288 16.9324 35.5524 16.4082 35.5524 15.7616C35.5524 15.115 35.0288 14.5908 34.3827 14.5908C33.7367 14.5908 33.213 15.115 33.213 15.7616C33.213 16.4082 33.7367 16.9324 34.3827 16.9324ZM4.68672 16.8641C5.33268 16.8641 5.85641 16.3399 5.85641 15.6934C5.85641 15.0468 5.33268 14.5226 4.68672 14.5226C4.04068 14.5226 3.51697 15.0468 3.51697 15.6934C3.51697 16.3399 4.04068 16.8641 4.68672 16.8641ZM11.5203 33.1356C11.5203 33.7822 10.9966 34.3064 10.3506 34.3064C9.70449 34.3064 9.18091 33.7822 9.18091 33.1356C9.18091 32.4891 9.70449 31.9649 10.3506 31.9649C10.9966 31.9649 11.5203 32.4891 11.5203 33.1356ZM28.7012 34.3271C29.3471 34.3271 29.8709 33.8029 29.8709 33.1563C29.8709 32.5096 29.3471 31.9854 28.7012 31.9854C28.0552 31.9854 27.5314 32.5096 27.5314 33.1563C27.5314 33.8029 28.0552 34.3271 28.7012 34.3271Z" fill="#25265E" fill-opacity="0.67"></path>
</g>
<defs>
<clippath id="clip0_2886_605">
<rect width="40" height="40" fill="white"></rect>
</clippath>
</defs>
</svg>
          </a>
        </div>
        <div class="editor-wrapper">
          <div class="editor-desktop-top-bar">
            <div class="file-name">main.cpp</div>
            <div class="desktop-top-bar__btn-wrapper">
              <button type="button" id="toggle-expanded-mode-desktop" title="Enter Fullscreen">
                <svg xmlns="http://www.w3.org/2000/svg" fill="rgba(37, 38, 94, 0.7)" viewBox="0 0 16 16" width="18" height="18" class="toggle-expanded-mode-mobile-icon expand svg replaced-svg">
  <path d="M5.038 2.22a.889.889 0 000-1.778v1.777zM.445 5.033a.889.889 0 101.778 0H.445zm13.334 0a.889.889 0 001.777 0H13.78zM10.964.44a.889.889 0 000 1.778V.441zm0 13.334a.889.889 0 000 1.778v-1.778zm4.592-2.815a.889.889 0 00-1.777 0h1.777zm-13.333 0a.889.889 0 00-1.778 0h1.778zm2.815 4.593a.889.889 0 000-1.778v1.778zm0-15.111H2.815v1.777h2.223V.442zm-2.223 0a2.37 2.37 0 00-2.37 2.37h1.778c0-.327.265-.593.592-.593V.442zm-2.37 2.37v2.222h1.778V2.812H.445zm15.111 2.222V2.812H13.78v2.222h1.777zm0-2.222a2.37 2.37 0 00-2.37-2.37v1.777c.327 0 .593.265.593.593h1.777zm-2.37-2.37h-2.222v1.777h2.222V.441zm-2.222 15.11h2.222v-1.777h-2.222v1.778zm2.222 0a2.37 2.37 0 002.37-2.37H13.78a.593.593 0 01-.593.593v1.778zm2.37-2.37V10.96H13.78v2.222h1.777zM.446 10.96v2.222h1.777V10.96H.445zm0 2.222a2.37 2.37 0 002.37 2.37v-1.777a.593.593 0 01-.593-.593H.445zm2.37 2.37h2.222v-1.777H2.816v1.778z" fill-opacity=".7"></path>
</svg>
                <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="18" height="18" fill="rgba(37, 38, 94, 0.7)" class="toggle-expanded-mode-mobile-icon minimize hidden svg replaced-svg">
  <path fill="#25265E" fill-opacity=".7" d="M5.926 1.334a.889.889 0 10-1.778 0h1.778zM1.333 4.15a.889.889 0 100 1.778V4.149zm13.334 1.778a.889.889 0 000-1.778v1.778zm-2.815-4.593a.889.889 0 00-1.778 0h1.778zm-1.778 13.334a.889.889 0 001.778 0h-1.778zm4.593-2.815a.889.889 0 000-1.778v1.778zM1.334 10.075a.889.889 0 000 1.778v-1.778zm2.814 4.593a.889.889 0 001.778 0H4.148zm0-13.334v2.223h1.778V1.334H4.148zm0 2.223a.593.593 0 01-.592.592v1.778a2.37 2.37 0 002.37-2.37H4.148zm-.592.592H1.333v1.778h2.223V4.149zm11.11 0h-2.221v1.778h2.222V4.149zm-2.221 0a.593.593 0 01-.593-.593h-1.778a2.37 2.37 0 002.37 2.37V4.15zm-.593-.593V1.334h-1.778v2.222h1.778zm0 11.112v-2.222h-1.778v2.222h1.778zm0-2.222c0-.328.265-.593.593-.593v-1.778a2.37 2.37 0 00-2.37 2.37h1.777zm.593-.593h2.222v-1.778h-2.222v1.778zm-11.111 0h2.222v-1.778H1.334v1.778zm2.222 0c.327 0 .592.265.592.593h1.778a2.37 2.37 0 00-2.37-2.37v1.777zm.592.593v2.222h1.778v-2.222H4.148z"></path>
</svg>
              </button>
              <button type="button" id="toggle-dark-mode-desktop" title="Toggle dark mode">
                <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="toggle-dark-mode-mobile-icon moon svg replaced-svg">
  <path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"></path>
</svg>
                <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="toggle-dark-mode-mobile-icon sun svg replaced-svg">
  <circle cx="12" cy="12" r="5"></circle>
  <line x1="12" y1="1" x2="12" y2="3"></line>
  <line x1="12" y1="21" x2="12" y2="23"></line>
  <line x1="4.22" y1="4.22" x2="5.64" y2="5.64"></line>
  <line x1="18.36" y1="18.36" x2="19.78" y2="19.78"></line>
  <line x1="1" y1="12" x2="3" y2="12"></line>
  <line x1="21" y1="12" x2="23" y2="12"></line>
  <line x1="4.22" y1="19.78" x2="5.64" y2="18.36"></line>
  <line x1="18.36" y1="5.64" x2="19.78" y2="4.22"></line>
</svg>
              </button>
              <button class="desktop-save-button" style="display: none">
                <span>
                  &nbsp;Save&nbsp;
                </span>
              </button>
              <button class="desktop-run-button run" style="cursor: pointer;">
                <span class="run-text">
                                &nbsp;Run&nbsp;
                              </span>
    

    

    

    

    

              </button>
            </div>
          </div>
          <button class="mobile-run-button run">
            Run
          </button>
          <div id="editor" class=" ace_editor ace-tm" style="font-family: droid_sans_monoregular; font-size: 14px; line-height: 22px; height: 528px;"><textarea class="ace_text-input" wrap="off" autocorrect="off" autocapitalize="off" spellcheck="false" style="opacity: 0; font-size: 1px; height: 1px; width: 1px; top: 220px; left: 99px;"></textarea><div class="ace_gutter" aria-hidden="true" style="left: 0px; width: 51px;"><div class="ace_layer ace_gutter-layer ace_folding-enabled" style="height: 1e+06px; top: 0px; left: 0px; width: 51px;"><div class="ace_gutter-cell " style="height: 22px; top: 0px;">1<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 22px;">2<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 44px;">3<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 66px;">4<span style="display: inline-block; height: 22px;" class="ace_fold-widget ace_start ace_open"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 88px;">5<span style="display: inline-block; height: 22px;" class="ace_fold-widget ace_start ace_open"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 110px;">6<span style="display: none; height: 22px;" class="ace_fold-widget ace_start ace_open"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 132px;">7<span style="display: none; height: 22px;" class="ace_fold-widget ace_start ace_open"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 154px;">8<span style="display: inline-block; height: 22px;" class="ace_fold-widget ace_start ace_open"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 176px;">9<span style="display: none; height: 22px;" class="ace_fold-widget ace_start ace_open"></span></div><div class="ace_gutter-cell ace_gutter-active-line " style="height: 22px; top: 198px;">10<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 220px;">11<span class="ace_fold-widget ace_start ace_open" style="display: none; height: 22px;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 242px;">12<span class="ace_fold-widget ace_start ace_open" style="display: none; height: 22px;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 264px;">13<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 286px;">14<span class="ace_fold-widget ace_start ace_open" style="display: none; height: 22px;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 308px;">15<span class="ace_fold-widget ace_start ace_open" style="display: none; height: 22px;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 330px;">16<span class="ace_fold-widget ace_start ace_open" style="display: inline-block; height: 22px;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 352px;">17<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 374px;">18<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 396px;">19<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 418px;">20<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 440px;">21<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 462px;">22<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 484px;">23<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 506px;">24<span style="display: none;"></span></div></div></div><div class="ace_scroller" style="line-height: 22px; left: 51px; right: 0px; bottom: 0px;"><div class="ace_content" style="top: 0px; left: 0px; width: 688px; height: 572px;"><div class="ace_layer ace_print-margin-layer"><div class="ace_print-margin" style="left: 708px; visibility: hidden;"></div></div><div class="ace_layer ace_marker-layer"><div class="ace_active-line" style="height: 22px; top: 198px; left: 0px; right: 0px;"></div><div class="ace_bracket ace_start ace_br15" style="height: 22px; width: 8.80078px; top: 198px; left: 39.2031px;"></div><div class="ace_bracket ace_start ace_br15" style="height: 22px; width: 8.80078px; top: 154px; left: 109.609px;"></div></div><div class="ace_layer ace_text-layer" style="height: 1e+06px; margin: 0px 4px; top: 0px; left: 0px;"><div class="ace_line_group" style="height: 22px; top: 0px;"><div class="ace_line" style="height: 22px;"><span class="ace_comment">// Online C++ compiler to run C++ program online</span></div></div><div class="ace_line_group" style="height: 22px; top: 22px;"><div class="ace_line" style="height: 22px;"><span class="ace_keyword">#include</span><span class="ace_constant ace_other"> &lt;iostream&gt;</span></div></div><div class="ace_line_group" style="height: 22px; top: 44px;"><div class="ace_line" style="height: 22px;"><span class="ace_keyword ace_control">using</span> <span class="ace_keyword ace_operator">namespace</span> <span class="ace_identifier">std</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 66px;"><div class="ace_line" style="height: 22px;"><span class="ace_storage ace_type">int</span> <span class="ace_identifier">fibonacci</span><span class="ace_paren ace_lparen">(</span><span class="ace_storage ace_type">int</span> <span class="ace_identifier">n</span><span class="ace_paren ace_rparen">)</span><span class="ace_paren ace_lparen">{</span></div></div><div class="ace_line_group" style="height: 22px; top: 88px;"><div class="ace_line" style="height: 22px;">    <span class="ace_keyword ace_control">if</span><span class="ace_paren ace_lparen">(</span><span class="ace_identifier">n</span><span class="ace_keyword ace_operator">==</span><span class="ace_constant ace_numeric">0</span><span class="ace_paren ace_rparen">)</span><span class="ace_paren ace_lparen">{</span></div></div><div class="ace_line_group" style="height: 22px; top: 110px;"><div class="ace_line" style="height: 22px;"><span class="ace_indent-guide">    </span>    <span class="ace_keyword ace_control">return</span> <span class="ace_constant ace_numeric">0</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 132px;"><div class="ace_line" style="height: 22px;">    <span class="ace_paren ace_rparen">}</span></div></div><div class="ace_line_group" style="height: 22px; top: 154px;"><div class="ace_line" style="height: 22px;">    <span class="ace_keyword ace_control">if</span><span class="ace_paren ace_lparen">(</span><span class="ace_identifier">n</span><span class="ace_keyword ace_operator">==</span><span class="ace_constant ace_numeric">1</span><span class="ace_paren ace_rparen">)</span><span class="ace_paren ace_lparen">{</span></div></div><div class="ace_line_group" style="height: 22px; top: 176px;"><div class="ace_line" style="height: 22px;"><span class="ace_indent-guide">    </span>    <span class="ace_keyword ace_control">return</span> <span class="ace_constant ace_numeric">1</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 198px;"><div class="ace_line" style="height: 22px;">    <span class="ace_paren ace_rparen">}</span></div></div><div class="ace_line_group" style="height: 22px; top: 220px;"><div class="ace_line" style="height: 22px;">    <span class="ace_storage ace_type">int</span> <span class="ace_identifier">ans</span><span class="ace_keyword ace_operator">=</span><span class="ace_identifier">fibonacci</span><span class="ace_paren ace_lparen">(</span><span class="ace_identifier">n</span><span class="ace_constant ace_numeric">-1</span><span class="ace_paren ace_rparen">)</span><span class="ace_keyword ace_operator">+</span><span class="ace_identifier">fibonacci</span><span class="ace_paren ace_lparen">(</span><span class="ace_identifier">n</span><span class="ace_constant ace_numeric">-2</span><span class="ace_paren ace_rparen">)</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 242px;"><div class="ace_line" style="height: 22px;">    <span class="ace_keyword ace_control">return</span> <span class="ace_identifier">ans</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 264px;"><div class="ace_line" style="height: 22px;"><span class="ace_paren ace_rparen">}</span></div></div><div class="ace_line_group" style="height: 22px; top: 286px;"><div class="ace_line" style="height: 22px;"></div></div><div class="ace_line_group" style="height: 22px; top: 308px;"><div class="ace_line" style="height: 22px;"></div></div><div class="ace_line_group" style="height: 22px; top: 330px;"><div class="ace_line" style="height: 22px;"><span class="ace_storage ace_type">int</span> <span class="ace_identifier">main</span><span class="ace_paren ace_lparen">(</span><span class="ace_paren ace_rparen">)</span> <span class="ace_paren ace_lparen">{</span></div></div><div class="ace_line_group" style="height: 22px; top: 352px;"><div class="ace_line" style="height: 22px;">    <span class="ace_storage ace_type">int</span> <span class="ace_identifier">n</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 374px;"><div class="ace_line" style="height: 22px;">    <span class="ace_identifier">cin</span><span class="ace_keyword ace_operator">&gt;&gt;</span><span class="ace_identifier">n</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 396px;"><div class="ace_line" style="height: 22px;">   </div></div><div class="ace_line_group" style="height: 22px; top: 418px;"><div class="ace_line" style="height: 22px;">    <span class="ace_storage ace_type">int</span> <span class="ace_identifier">value</span><span class="ace_keyword ace_operator">=</span><span class="ace_identifier">fibonacci</span><span class="ace_paren ace_lparen">(</span><span class="ace_identifier">n</span><span class="ace_paren ace_rparen">)</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 440px;"><div class="ace_line" style="height: 22px;">    <span class="ace_identifier">cout</span><span class="ace_keyword ace_operator">&lt;&lt;</span><span class="ace_identifier">value</span><span class="ace_keyword ace_operator">&lt;&lt;</span><span class="ace_identifier">endl</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 462px;"><div class="ace_line" style="height: 22px;"></div></div><div class="ace_line_group" style="height: 22px; top: 484px;"><div class="ace_line" style="height: 22px;">    <span class="ace_keyword ace_control">return</span> <span class="ace_constant ace_numeric">0</span><span class="ace_punctuation ace_operator">;</span></div></div><div class="ace_line_group" style="height: 22px; top: 506px;"><div class="ace_line" style="height: 22px;"><span class="ace_paren ace_rparen">}</span></div></div></div><div class="ace_layer ace_marker-layer"></div><div class="ace_layer ace_cursor-layer ace_hidden-cursors"><div class="ace_cursor" style="display: block; top: 198px; left: 48px; width: 9px; height: 22px; animation-duration: 1000ms;"></div></div></div></div><div class="ace_scrollbar ace_scrollbar-v" style="display: none; width: 22px; bottom: 0px;"><div class="ace_scrollbar-inner" style="width: 22px; height: 528px;">&nbsp;</div></div><div class="ace_scrollbar ace_scrollbar-h" style="display: none; height: 22px; left: 51px; right: 0px;"><div class="ace_scrollbar-inner" style="height: 22px; width: 688px;">&nbsp;</div></div><div style="height: auto; width: auto; top: 0px; left: 0px; visibility: hidden; position: absolute; white-space: pre; font: inherit; overflow: hidden;"><div style="height: auto; width: auto; top: 0px; left: 0px; visibility: hidden; position: absolute; white-space: pre; font: inherit; overflow: visible;">הההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההה</div><div style="height: auto; width: auto; top: 0px; left: 0px; visibility: hidden; position: absolute; white-space: pre; font-style: inherit; font-variant: inherit; font-stretch: inherit; font-size: inherit; line-height: inherit; font-family: inherit; font-optical-sizing: inherit; font-kerning: inherit; font-feature-settings: inherit; font-variation-settings: inherit; overflow: visible;">XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</div></div></div>
        </div>

        <div class="terminal-wrapper">
          <div class="terminal-desktop-top-bar">
            <div class="shell-name">
              Output            </div>
            <div class="terminal-desktop-top-bar__btn-wrapper">
              <button class="desktop-clear-button">
                  &nbsp;Clear&nbsp;
              </button>
            </div>
          </div>
          <div id="terminal" class=" ace_editor ace-tm" style="font-family: droid_sans_monoregular; font-size: 14px; line-height: 22px; height: 88px;"><textarea class="ace_text-input" wrap="off" autocorrect="off" autocapitalize="off" spellcheck="false" style="opacity: 0; font-size: 1px; height: 1px; width: 1px; top: 87px; left: 4px;"></textarea><div class="ace_gutter" aria-hidden="true" style="display: none; left: 0px; width: 42px;"><div class="ace_layer ace_gutter-layer ace_folding-enabled" style="height: 1e+06px; top: 0px; left: 0px; width: 42px;"><div class="ace_gutter-cell " style="height: 22px; top: 0px;">1<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 22px;">2<span style="display: none;"></span></div><div class="ace_gutter-cell " style="height: 22px; top: 44px;">3<span style="display: none;"></span></div><div class="ace_gutter-cell ace_gutter-active-line " style="height: 22px; top: 66px;">4<span style="display: none;"></span></div></div></div><div class="ace_scroller" style="line-height: 22px; left: 0px; right: 0px; bottom: 0px;"><div class="ace_content" style="top: 0px; left: 0px; width: 739px; height: 132px;"><div class="ace_layer ace_print-margin-layer"><div class="ace_print-margin" style="left: 708px; visibility: hidden;"></div></div><div class="ace_layer ace_marker-layer"></div><div class="ace_layer ace_text-layer" style="height: 1e+06px; margin: 0px 4px; top: 0px; left: 0px;"><div class="ace_line_group" style="height: 22px; top: 0px;"><div class="ace_line" style="height: 22px;"><span class="ace_comment ace_line ace_colons ace_dosbatch">/tmp/bh8VI2ShR7.o</span></div></div><div class="ace_line_group" style="height: 22px; top: 22px;"><div class="ace_line" style="height: 22px;">8</div></div><div class="ace_line_group" style="height: 22px; top: 44px;"><div class="ace_line" style="height: 22px;">21</div></div><div class="ace_line_group" style="height: 22px; top: 66px;"><div class="ace_line" style="height: 22px;"></div></div></div><div class="ace_layer ace_marker-layer"></div><div class="ace_layer ace_cursor-layer ace_slim-cursors ace_hidden-cursors"><div class="ace_cursor" style="display: block; top: 66px; left: 4px; width: 9px; height: 22px; animation-duration: 1000ms;"></div></div></div></div><div class="ace_scrollbar ace_scrollbar-v" style="display: none; width: 22px; bottom: 0px;"><div class="ace_scrollbar-inner" style="width: 22px; height: 88px;">&nbsp;</div></div><div class="ace_scrollbar ace_scrollbar-h" style="display: none; height: 22px; left: 0px; right: 0px;"><div class="ace_scrollbar-inner" style="height: 22px; width: 739px;">&nbsp;</div></div><div style="height: auto; width: auto; top: 0px; left: 0px; visibility: hidden; position: absolute; white-space: pre; font: inherit; overflow: hidden;"><div style="height: auto; width: auto; top: 0px; left: 0px; visibility: hidden; position: absolute; white-space: pre; font: inherit; overflow: visible;">הההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההההה</div><div style="height: auto; width: auto; top: 0px; left: 0px; visibility: hidden; position: absolute; white-space: pre; font-style: inherit; font-variant: inherit; font-stretch: inherit; font-size: inherit; line-height: inherit; font-family: inherit; font-optical-sizing: inherit; font-kerning: inherit; font-feature-settings: inherit; font-variation-settings: inherit; overflow: visible;">XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX</div></div></div>

          <div class="sale-popup" id="sale-popup">
            <div class="close-icon-container-sale">
                <button type="button" class="close-pop-up-btn close-sale-popup" title="Close Pop Up" style="margin: 0">
                  <svg xmlns="http://www.w3.org/2000/svg" width="10" height="10" viewBox="0 0 10 10" fill="none" class="svg-grey svg replaced-svg">
  <path fill-rule="evenodd" clip-rule="evenodd" d="M5.6524 5.12836L9.62115 1.08149C9.7919 0.895223 9.78428 0.607144 9.60393 0.430165C9.42358 0.253186 9.13541 0.251006 8.9524 0.425235L4.9899 4.46586L0.864901 0.418985C0.746807 0.294941 0.57046 0.245179 0.404942 0.289192C0.239424 0.333206 0.111087 0.463988 0.0702039 0.630307C0.0293208 0.796626 0.082401 0.972002 0.208651 1.08774L4.3274 5.12836L0.208651 9.16899C0.0344216 9.35199 0.0366021 9.64016 0.213581 9.82051C0.39056 10.0009 0.678639 10.0085 0.864901 9.83774L4.9899 5.79086L8.9524 9.83148C9.13541 10.0057 9.42358 10.0035 9.60393 9.82656C9.78428 9.64958 9.7919 9.3615 9.62115 9.17524L5.6524 5.12836Z" fill="#25265E" fill-opacity="0.67"></path>
</svg>
                </button>
            </div>

            <div class="sale-container">
              <h3 id="discount-description">
                C++ Course, Enhanced by AI
              </h3>
              <h5>
                Learn C++ the right way — solve challenges, build projects, and leverage the power of AI to aid you in handling errors.
              </h5>
            </div>
            <a id="claim-discount" href="https://programiz.pro/?utm_source=popup-compiler&amp;utm_medium=popup" title="Get Started for Free" class="run" target="_blank">
              Get Started for Free
            </a>
          </div>
        </div>
      </div>
    </div>

    <script defer="" type="text/javascript">

      const lang = "cpp";

      var playStoreUrl =
          "https://play.google.com/store/apps/details?id=com.programiz.learnpython",
        appStoreUrl =
          "https://apps.apple.com/app/apple-store/id1472188189?pt=120228772",
        desktopUrl = "https://www.programiz.com/learn-python";

      var os, a;

      a = document.getElementById("ad-link");
      b = document.getElementById("mobile-ad-link");

      let baseURL = "https://programiz.pro"

      let utm = "utm_source=compiler-nav&utm_campaign=programiz&utm_medium=referral"

      let uri = "learn"


      let href = `${baseURL}/${uri}/master-python?${utm}`;

      let app = "Python";

      if(lang == 'c') {
        href = `${baseURL}/${uri}/master-c-programming?${utm}`;
        app = "C";
      } else if(lang == 'java') {
        href = `${baseURL}/${uri}/master-java?${utm}`;
        app = "Java";
      }  else if(lang == 'cpp') {
        href = `${baseURL}/${uri}/master-cpp?${utm}`;
        app = "C++";
      }

      a.innerHTML = `${app} Certification ❯`;
      b.innerHTML = `${app} Course`;
      a.href = href;
      b.href = href;
    </script><iframe name="__tcfapiLocator" style="display: none;" src="./fibonacci_recurssion_files/saved_resource.html"></iframe><iframe name="__uspapiLocator" style="display: none;" src="./fibonacci_recurssion_files/saved_resource(1).html"></iframe>
    <!-- The use of the cloudflare cdn for all external libraries is intential. We are trying to reduce the number
         of DNS lookups.
    -->
    <script defer="" src="./fibonacci_recurssion_files/socket.io.min.js.download"></script>
    <script defer="" src="./fibonacci_recurssion_files/jquery.min.js.download"></script>

    <script defer="" src="./fibonacci_recurssion_files/ace.js.download"></script>
    <script defer="" src="./fibonacci_recurssion_files/mousetrap.min.js.download"></script>
    <script defer="" src="./fibonacci_recurssion_files/final.js.download"></script>

    <!-- Google Tag Manager (noscript) -->
    <noscript><iframe src="https://www.googletagmanager.com/ns.html?id=GTM-TKXT7MH"
    height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
    <!-- End Google Tag Manager (noscript) -->
  

<img src="./fibonacci_recurssion_files/favicon.ico" style="display: none !important; width: 1px !important; height: 1px !important;"><script>
		function returnCommentSymbol(language = "javascript") {
			const languageObject = {
				bat: "@REM",
				c: "//",
				csharp: "//",
				cpp: "//",
				closure: ";;",
				coffeescript: "#",
				dockercompose: "#",
				css: "/*DELIMITER*/",
				"cuda-cpp": "//",
				dart: "//",
				diff: "#",
				dockerfile: "#",
				fsharp: "//",
				"git-commit": "//",
				"git-rebase": "#",
				go: "//",
				groovy: "//",
				handlebars: "{{!--DELIMITER--}}",
				hlsl: "//",
				html: "<!--DELIMITER-->",
				ignore: "#",
				ini: ";",
				java: "//",
				javascript: "//",
				javascriptreact: "//",
				json: "//",
				jsonc: "//",
				julia: "#",
				latex: "%",
				less: "//",
				lua: "--",
				makefile: "#",
				markdown: "<!--DELIMITER-->",
				"objective-c": "//",
				"objective-cpp": "//",
				perl: "#",
				perl6: "#",
				php: "<!--DELIMITER-->",
				powershell: "#",
				properties: ";",
				jade: "//-",
				python: "#",
				r: "#",
				razor: "<!--DELIMITER-->",
				restructuredtext: "..",
				ruby: "#",
				rust: "//",
				scss: "//",
				shaderlab: "//",
				shellscript: "#",
				sql: "--",
				svg: "<!--DELIMITER-->",
				swift: "//",
				tex: "%",
				typescript: "//",
				typescriptreact: "//",
				vb: "'",
				xml: "<!--DELIMITER-->",
				xsl: "<!--DELIMITER-->",
				yaml: "#"
			}
			if(!languageObject[language]){
				return languageObject["python"].split("DELIMITER")
			}
			return languageObject[language].split("DELIMITER")
		}
		var savedChPos = 0
		var returnedSuggestion = ''
		let editor, doc, cursor, line, pos
		pos = {line: 0, ch: 0}
		var suggestionsStatus = false
		var docLang = "python"
		var suggestionDisplayed = false
		var isReturningSuggestion = false
		document.addEventListener("keydown", (event) => {
		setTimeout(()=>{
			editor = event.target.closest('.CodeMirror');
			if (editor){
				const codeEditor = editor.CodeMirror
				if(!editor.classList.contains("added-tab-function")){
					editor.classList.add("added-tab-function")
					codeEditor.removeKeyMap("Tab")
					codeEditor.setOption("extraKeys", {Tab: (cm)=>{

						if(returnedSuggestion){
							acceptTab(returnedSuggestion)
						}
						else{
							cm.execCommand("defaultTab")
						}
					}})
				}
				doc = editor.CodeMirror.getDoc()
				cursor = doc.getCursor()
				line = doc.getLine(cursor.line)
				pos = {line: cursor.line, ch: line.length}

				if(cursor.ch > 0){
					savedChPos = cursor.ch
				}

				const fileLang = doc.getMode().name
				docLang = fileLang
				const commentSymbol = returnCommentSymbol(fileLang)
				if (event.key == "?"){
					var lastLine = line
					lastLine = lastLine.slice(0, savedChPos - 1)

					if(lastLine.trim().startsWith(commentSymbol[0])){
						if(fileLang !== "null"){
							lastLine += " "+ fileLang
						}
						
						lastLine = lastLine.split(commentSymbol[0])[1]
						window.postMessage({source: 'getQuery', payload: { data: lastLine } } )
						isReturningSuggestion = true
						displayGrey("\nBlackbox loading...")
					}
				}else if(event.key === "Enter" && suggestionsStatus && !isReturningSuggestion){
					var query = doc.getRange({ line: Math.max(0,cursor.line-50), ch: 0 }, { line: cursor.line, ch: line.length })
					window.postMessage({source: 'getSuggestion', payload: { data: query, language: docLang, cursorPos: pos } } )
					displayGrey("Blackbox loading...")
				}else if(event.key === "ArrowRight" && returnedSuggestion){
					acceptTab(returnedSuggestion)
				}else if(event.key === "Enter" && isReturningSuggestion){
					displayGrey("\nBlackbox loading...")
				}else if(event.key === "Escape"){
					displayGrey("")
				}
			}
		}, 0)
		})

		function acceptTab(text){
		if (suggestionDisplayed){
			displayGrey("")
			doc.replaceRange(text, pos)
			returnedSuggestion = ""
			updateSuggestionStatus(false)
		}
		}
		function acceptSuggestion(text){
			displayGrey("")
			doc.replaceRange(text, pos)
			returnedSuggestion = ""
			updateSuggestionStatus(false)
		}
		function displayGrey(text){
			if(!text){
				document.querySelector(".blackbox-suggestion").remove()
				return
			}
			var el = document.querySelector(".blackbox-suggestion")
			if(!el){
				el = document.createElement('span')
				el.classList.add("blackbox-suggestion")
				el.style = 'color:grey'
				el.innerText = text
			}
			else{
				el.innerText = text
			}
			
			var lineIndex = pos.line;
			editor.getElementsByClassName('CodeMirror-line')[lineIndex].appendChild(el)
		}
		function updateSuggestionStatus(s){
			suggestionDisplayed = s
			window.postMessage({source: 'updateSuggestionStatus', status: suggestionDisplayed, suggestion: returnedSuggestion})
		}
		window.addEventListener('message', (event)=>{
		if (event.source !== window ) return
		if (event.data.source == 'return'){
			isReturningSuggestion = false
			const formattedCode = formatCode(event.data.payload.data)
			returnedSuggestion = formattedCode
			displayGrey(formattedCode)
			updateSuggestionStatus(true)
		}
		if(event.data.source == 'suggestReturn'){
			const prePos = event.data.payload.cursorPos
			if(pos.line == prePos.line && pos.ch == prePos.ch){
				returnedSuggestion = event.data.payload.data
				displayGrey(event.data.payload.data)
				updateSuggestionStatus(true)
			}
			else{
				displayGrey()
			}
		}
		if(event.data.source == 'codeSearchReturn'){
			isReturningSuggestion = false
			displayGrey()
		}
		if(event.data.source == 'suggestionsStatus'){
			suggestionsStatus = event.data.payload.enabled
		}
		if(event.data.source == 'acceptSuggestion'){
			
			acceptSuggestion(event.data.suggestion)
		}
		})
		document.addEventListener("keyup", function(){
			returnedSuggestion = ""
			updateSuggestionStatus(false)
		})
		function formatCode(data) {
			if (Array.isArray(data)) {
				var finalCode = ""
				var pairs = []
		
				const commentSymbol = returnCommentSymbol(docLang)
				data.forEach((codeArr, idx) => {
					const code = codeArr[0]
					var desc = codeArr[1]
					const descArr = desc.split("\n")
					var finalDesc = ""
					descArr.forEach((descLine, idx) => {
						const whiteSpace = descLine.search(/\S/)
						if (commentSymbol.length < 2 || idx === 0) {
							finalDesc += insert(descLine, whiteSpace, commentSymbol[0])
						}
						if (commentSymbol.length > 1 && idx === descArr.length - 1) {
							finalDesc = finalDesc + commentSymbol[1] + "\n"
						}
					})
		
					finalCode += finalDesc + "\n\n" + code
					pairs.push(finalCode)
				})
				return "\n"+pairs.join("\n")
			}
		
			return "\n"+data
		}
		
		function insert(str, index, value) {
			return str.substr(0, index) + value + str.substr(index)
		}
	</script><iframe src="./fibonacci_recurssion_files/container.html" style="visibility: hidden; display: none;"></iframe><quillbot-extension-portal><template shadowrootmode="open"><div></div></template></quillbot-extension-portal><iframe src="./fibonacci_recurssion_files/syncframe.html" width="0" height="0" frameborder="0" title="Criteo GUM iframe" style="border-width: 0px; margin: 0px; display: none;"></iframe><div><iframe src="./fibonacci_recurssion_files/pd.html" width="0" height="0" style="display:none;"></iframe></div><iframe src="./fibonacci_recurssion_files/aframe.html" width="0" height="0" style="display: none;"></iframe></body><quillbot-extension-root><template shadowrootmode="open" shadowrootdelegatesfocus><div id="qb-ext-sr"><div style="display: none;"><button class="MuiButton-root MuiButton-primary MuiButton-primaryPrimary MuiButton-sizeSmall MuiButton-primarySizeSmall MuiButtonBase-root extn-css-1mbubfb" tabindex="0" type="button" appearance="brand"><span class="MuiTouchRipple-root extn-css-w0pj6f"></span></button></div><style data-styled="active" data-styled-version="5.3.5">*,::before,::after{box-sizing:border-box;border-width:0;border-style:solid;--tw-border-opacity:1;border-color:rgba(229,231,235,var(--tw-border-opacity));--tw-translate-x:0;--tw-translate-y:0;--tw-rotate:0;--tw-skew-x:0;--tw-skew-y:0;--tw-scale-x:1;--tw-scale-y:1;--tw-transform:translateX(var(--tw-translate-x)) translateY(var(--tw-translate-y)) rotate(var(--tw-rotate)) skewX(var(--tw-skew-x)) skewY(var(--tw-skew-y)) scaleX(var(--tw-scale-x)) scaleY(var(--tw-scale-y));--tw-ring-inset:var(--tw-empty,/*!*/ /*!*/);--tw-ring-offset-width:0px;--tw-ring-offset-color:#fff;--tw-ring-color:rgba(59,130,246,0.5);--tw-ring-offset-shadow:0 0 #0000;--tw-ring-shadow:0 0 #0000;--tw-shadow:0 0 #0000;--tw-blur:var(--tw-empty,/*!*/ /*!*/);--tw-brightness:var(--tw-empty,/*!*/ /*!*/);--tw-contrast:var(--tw-empty,/*!*/ /*!*/);--tw-grayscale:var(--tw-empty,/*!*/ /*!*/);--tw-hue-rotate:var(--tw-empty,/*!*/ /*!*/);--tw-invert:var(--tw-empty,/*!*/ /*!*/);--tw-saturate:var(--tw-empty,/*!*/ /*!*/);--tw-sepia:var(--tw-empty,/*!*/ /*!*/);--tw-drop-shadow:var(--tw-empty,/*!*/ /*!*/);--tw-filter:var(--tw-blur) var(--tw-brightness) var(--tw-contrast) var(--tw-grayscale) var(--tw-hue-rotate) var(--tw-invert) var(--tw-saturate) var(--tw-sepia) var(--tw-drop-shadow);--tw-backdrop-blur:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-brightness:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-contrast:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-grayscale:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-hue-rotate:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-invert:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-opacity:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-saturate:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-sepia:var(--tw-empty,/*!*/ /*!*/);--tw-backdrop-filter:var(--tw-backdrop-blur) var(--tw-backdrop-brightness) var(--tw-backdrop-contrast) var(--tw-backdrop-grayscale) var(--tw-backdrop-hue-rotate) var(--tw-backdrop-invert) var(--tw-backdrop-opacity) var(--tw-backdrop-saturate) var(--tw-backdrop-sepia);}html{line-height:1.5;-webkit-text-size-adjust:100%;-moz-tab-size:4;tab-size:4;font-family:ui-sans-serif,system-ui,-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";}body{margin:0;font-family:inherit;line-height:inherit;}hr{height:0;color:inherit;border-top-width:1px;}abbr[title]{-webkit-text-decoration:underline dotted;text-decoration:underline dotted;}b,strong{font-weight:bolder;}code,kbd,samp,pre{font-family:ui-monospace,SFMono-Regular,Consolas,'Liberation Mono',Menlo,monospace;font-size:1em;}small{font-size:80%;}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline;}sub{bottom:-0.25em;}sup{top:-0.5em;}table{text-indent:0;border-color:inherit;border-collapse:collapse;}button,input,optgroup,select,textarea{font-family:inherit;font-size:100%;line-height:inherit;margin:0;padding:0;color:inherit;}button,select{text-transform:none;}button,[type='button'],[type='reset'],[type='submit']{-webkit-appearance:button;}::-moz-focus-inner{border-style:none;padding:0;}:-moz-focusring{outline:1px dotted ButtonText;}:-moz-ui-invalid{box-shadow:none;}legend{padding:0;}progress{vertical-align:baseline;}::-webkit-inner-spin-button,::-webkit-outer-spin-button{height:auto;}[type='search']{-webkit-appearance:textfield;outline-offset:-2px;}::-webkit-search-decoration{-webkit-appearance:none;}::-webkit-file-upload-button{-webkit-appearance:button;font:inherit;}summary{display:list-item;}blockquote,dl,dd,h1,h2,h3,h4,h5,h6,hr,figure,p,pre{margin:0;}button{background-color:transparent;background-image:none;}fieldset{margin:0;padding:0;}ol,ul{list-style:none;margin:0;padding:0;}img{border-style:solid;}textarea{resize:vertical;}input::-webkit-input-placeholder,textarea::-webkit-input-placeholder{color:#9ca3af;}input::-moz-placeholder,textarea::-moz-placeholder{color:#9ca3af;}input:-ms-input-placeholder,textarea:-ms-input-placeholder{color:#9ca3af;}input::placeholder,textarea::placeholder{color:#9ca3af;}button,[role="button"]{cursor:pointer;}h1,h2,h3,h4,h5,h6{font-size:inherit;font-weight:inherit;}a{color:inherit;-webkit-text-decoration:inherit;text-decoration:inherit;}pre,code,kbd,samp{font-family:ui-monospace,SFMono-Regular,Menlo,Monaco,Consolas,"Liberation Mono","Courier New",monospace;}img,svg,video,canvas,audio,iframe,embed,object{display:block;vertical-align:middle;}img,video{max-width:100%;height:auto;}[hidden]{display:none;}@-webkit-keyframes spin{to{-webkit-transform:rotate(360deg);-ms-transform:rotate(360deg);transform:rotate(360deg);}}@keyframes spin{to{-webkit-transform:rotate(360deg);-ms-transform:rotate(360deg);transform:rotate(360deg);}}@-webkit-keyframes ping{75%,100%{-webkit-transform:scale(2);-ms-transform:scale(2);transform:scale(2);opacity:0;}}@keyframes ping{75%,100%{-webkit-transform:scale(2);-ms-transform:scale(2);transform:scale(2);opacity:0;}}@-webkit-keyframes pulse{50%{opacity:.5;}}@keyframes pulse{50%{opacity:.5;}}@-webkit-keyframes bounce{0%,100%{-webkit-transform:translateY(-25%);-ms-transform:translateY(-25%);transform:translateY(-25%);-webkit-animation-timing-function:cubic-bezier(0.8,0,1,1);animation-timing-function:cubic-bezier(0.8,0,1,1);}50%{-webkit-transform:none;-ms-transform:none;transform:none;-webkit-animation-timing-function:cubic-bezier(0,0,0.2,1);animation-timing-function:cubic-bezier(0,0,0.2,1);}}@keyframes bounce{0%,100%{-webkit-transform:translateY(-25%);-ms-transform:translateY(-25%);transform:translateY(-25%);-webkit-animation-timing-function:cubic-bezier(0.8,0,1,1);animation-timing-function:cubic-bezier(0.8,0,1,1);}50%{-webkit-transform:none;-ms-transform:none;transform:none;-webkit-animation-timing-function:cubic-bezier(0,0,0.2,1);animation-timing-function:cubic-bezier(0,0,0.2,1);}}</style></div><style id="common-css">[contenteditable]:focus {
  outline: 0px solid transparent;
}

:root {
  --new: #499557;
  --new-hover: #41894e;
  --new-secondary: #71b657;
  --new-filter: saturate(150%) hue-rotate(25deg) brightness(92%);
  --new-filter-hover: brightness(90%);
  --new-banner: #6aab76;
  --new-banner-hover: #65986f;

  --traditional-filter: none;
  --traditional-filter-hover: none;
  --traditional-secondary: #8aad67;
  --traditional: #849e63;
  --traditional-hover: #687b50;
  --traditional-banner: #99b576;
  --traditional-banner-hover: #799655;

  --primary: var(--new);
  --secondary: var(--new-secondary);
  --primary-hover: var(--new-hover);
  --image-filter: var(--new-filter);
  --image-filter-hover: var(--new-filter-hover);
  --banner: var(--new-banner);
  --banner-hover: var(--new-banner-hover);

  --default-font: Lato, sans-serif;
}

body {
  background: #fff;
  justify-content: center;
  text-rendering: optimizelegibility;
  margin: 0 !important;
}

.mobile-quill-bottom-controls > div {
  min-width: 48px;
}

textarea {
  resize: none;
}

a {
  text-decoration: none;
  color: white;
}

/* .title {
  width: 500px;
  font-size: 1.5rem;
  display: inline-block;
} */

.btn {
  -moz-user-select: none;
  -khtml-user-select: none;
  -webkit-user-select: none;
  -ms-user-select: none;
  user-select: none;
  transition: all 0.3s;
}

/* hide google re-captcha */

.go-premium-btn {
  width: 150px;
  text-align: center;
  padding: 4px 20px !important;
  margin: auto;
  font-weight: bold !important;
  color: #fff;
  cursor: pointer;
}

.no-box-shadow {
  box-shadow: none !important;
}

.login-offer-text {
  margin: -2px 2px;
}

.green-text {
  transition: all 0.15s;
  color: var(--primary);
  cursor: pointer;
}

.green-text:hover {
  color: var(--primary-hover);
}

.word-prompt-items {
  display: flex;
}

.article-sentence {
  display: inline;
  -webkit-transition: all 0.15s;
  -moz-transition: all 0.15s;
  -o-transition: all 0.15s;
  -ms-transition: all 0.15s;
  transition: all 0.15s;
  /* padding: 4.5px 0px; */
}

.similarity-score {
  color: black;
  font-size: 0.65em;
  margin-left: 5px;
}

.error-message {
  color: #ee1212;
  font-family: Lato, serif;
  font-size: 0.8rem;
  text-align: center;
  line-height: 18px;
  width: 100%;
  display: block;
}

.success-message {
  color: #00ff00;
  font-family: Lato, serif;
  font-size: 0.8rem;
  text-align: center;
  line-height: 18px;
}

.color-scale {
  width: 100%;
  height: 12px;
  display: flex;
  justify-content: space-around;
  padding: 2px;
  margin-top: 6px;
  margin-left: -1px;
}

.color-button {
  width: 12px;
  height: 12px;
  cursor: pointer;
  border-radius: 8px;
  border: 2px solid #737373;
  margin-top: -2px;
  margin: 8px 8px;
  transition: all 0.1s;
}

.color-button-inside {
  width: 8px;
  height: 8px;
  cursor: pointer;
  border-radius: 8px;
  transition: all 0.1s;
  margin-top: -2px;
  margin: 2px 2px;
}

.article-color-button {
  background-color: #f8f8f8;
  width: 10px;
  height: 10px;
  cursor: pointer;
  border-radius: 8px;
  border: 2px solid #737373;
  margin-top: -2px;
  margin: 3px 4px;
  transition: all 0.1s;
}

.article-color-button-inside {
  background-color: #f8f8f8;
  width: 8px;
  height: 8px;
  cursor: pointer;
  border-radius: 8px;
  margin-top: -2px;
  margin: 1px 1px;
  transition: all 0.1s;
}

.recaptcha-container {
  position: absolute;
}

#example1 {
  transition: all 0.1s;
}

.processing-payment {
  position: absolute;
  background-color: #fff;
  width: 100%;
  height: 100%;
  margin: auto;
  margin-top: 0;
  margin-left: 0;
  text-align: center;
  left: 0px;
  top: 0px;
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 1;
}

.my-tooltip {
  line-height: 20px;
  font-size: 0.9em;
  width: 210px;
  text-align: center;
  transition: all 0s;
  z-index: 9000000;
}

.my-tooltip > h6 {
  line-height: 0px;
  margin-top: 18px;
  font-size: 0.9em;
  margin-bottom: 18px;
  filter: brightness(100);
  text-align: center;
  transition: all 0s;
}

.p-lock {
  margin-left: 1px;
  width: 14px;
  height: 14px;
  opacity: 0.69;
}

.ap-lock {
  width: 12px;
  height: 12px;
  opacity: 0.69;
  margin-top: 3px;
  cursor: pointer;
}

.strength-list {
  display: flex;
  margin-top: 6px;
  flex-direction: column;
  margin-left: 4px;
}

.strength-list-row {
  display: flex;
  cursor: pointer;
}

.strength-tag {
  color: rgb(86, 86, 86);
  font-size: 0.8em;
  line-height: 33px;
  font-weight: bold;
}

.priority-divider {
  border-top: 1px solid rgb(153, 153, 153);
  width: 70%;
  margin-left: 5%;
  margin-top: 7px;
  margin-bottom: 3px;
  margin-left: 12%;
  margin-right: auto;
}

.credit-cards {
  margin-right: 0px;
  cursor: pointer;
}

.credit-cards img {
  padding-right: 5px;
}

.paypal-logo-click {
  cursor: pointer;
}

.article-copy-textarea {
  width: 100%;
  height: 100%;
  padding: 5px;
  font-family: Lato, sans-serif;
  font-size: 1em;
}

/* ::-webkit-scrollbar {
  width: 5px;
  cursor: default;
}
*/
/* Track */
/* ::-webkit-scrollbar-track {
  border-radius: 10px;
} */

/* Handle */
/* ::-webkit-scrollbar-thumb {
  background: gray;
} */

/* Loader css */
#overlay {
  background: #000000;
  /* color: #666666; */
  position: fixed;
  height: 100%;
  width: 100%;
  z-index: 5000;
  top: 0;
  left: 0;
  float: left;
  text-align: center;
  padding-top: 25%;
  opacity: 0.4;
}

.spinner {
  margin: 0 auto;
  height: 64px;
  width: 64px;
  animation: rotate 0.8s infinite linear;
  border: 5px solid;
  border-right-color: transparent;
  border-radius: 50%;
}

.hotkey-command {
  /* color: #8f8f8f !important; */
}

@keyframes rotate {
  0% {
    transform: rotate(0deg);
  }

  100% {
    transform: rotate(360deg);
  }
}

/*================ new css code for new project ====================== */

.container {
  max-width: 1300px;
  margin: auto;
  padding: 0px 12px;
  width: 100%;
}

.extHeader {
  /* background: #f1f7f3; */
  position: sticky;
  top: 0;
  z-index: 1;
}

.maximizeouticon {
  width: 35px;
  background: #828282;
  height: 3px;
  margin: auto;
  border-radius: 5px;
  margin-bottom: 11px;
  display: block;
}

.kebabBtn {
  padding: 6px 0px;
  text-align: right;
}

@media all and (-ms-high-contrast: none), (-ms-high-contrast: active) {
  :root {
    --new: #499557;
    --new-hover: #41894e;
    --new-secondary: #71b657;
    --new-filter: saturate(150%) hue-rotate(25deg) brightness(92%);
    --new-filter-hover: brightness(90%);
    --new-banner: #6aab76;
    --new-banner-hover: #65986f;

    --traditional-filter: none;
    --traditional-filter-hover: none;
    --traditional-secondary: #8aad67;
    --traditional: #849e63;
    --traditional-hover: #687b50;
    --traditional-banner: #99b576;
    --traditional-banner-hover: #799655;

    --primary: var(--new);
    --secondary: #71b657;
    --primary-hover: #41894e;
    --image-filter: var(--new-filter);
    --image-filter-hover: var(--new-filter-hover);
    --banner: var(--new-banner);
    --banner-hover: var(--new-banner-hover);

    --default-font: Lato, sans-serif;
  }

  body {
    text-rendering: optimizelegibility;
    margin: 0 !important;
  }

  .manual-payment-container {
    margin: auto;
    margin-top: auto;
    text-align: center;
    max-width: 400px;
    width: 100%;
    display: block;
    padding: 10px;
    border: 0px solid #499557;
    border-radius: 6px;
    margin-top: 20px;
    min-height: 162px;
  }

  .processing-payment {
    position: absolute;
    background-color: #ccc;
    opacity: 0.4;
    height: 100%;
    margin: auto;
    left: 0px;
    top: 0px;
    width: 100%;
    text-align: center;
  }

  .__react_component_tooltip.show {
    opacity: 1;
    transition: all 0s;
  }

  .green-text {
    transition: all 0.15s;
    color: #499557;
    cursor: pointer;
  }

  .green-text:hover {
    color: #41894e;
  }
}

/* Forcing font everywhere to be open sans. This not working*/
body {
  font-family: 'Open Sans', sans-serif !important;
  font-size: 14px;
  overscroll-behavior-y: contain;
  background: #fff;
}

/*
using in commented code
.nd-input-toast-container {
  bottom: 25px;
  width: calc(100% - 20px);
  background: #2c2d33;
  text-align: center;
  font-family: monospace;
  padding: 5px;
  border-radius: 0px 0px 5px 5px;
  margin: 2px 5px 5px 5px;
  color: white;
}*/

.nd-word {
  transition: all 0.05s;
  position: relative;
}

/* #inputText[placeholder]:empty::before { // check
  content: attr(placeholder);
  color: #8497aa;
} */

#inputText[placeholder]:empty:focus::before {
  content: '';
}

/* #inputBoxSummarizer[placeholder]:empty::before {
  content: attr(placeholder);
  color: #dcdcdc;
} */

#inputBoxSummarizer[placeholder]:empty:focus::before {
  content: '';
}

/* ============= new design 2 css ================= */

/* start of CSS for splitter */
.Resizer {
  background: #000;
  opacity: 0.2;
  z-index: 1;
  -moz-box-sizing: border-box;
  -webkit-box-sizing: border-box;
  box-sizing: border-box;
  -moz-background-clip: padding;
  -webkit-background-clip: padding;
  background-clip: padding-box;
}

.Pane {
  display: flex;
}

/* .Resizer:hover {
  -webkit-transition: all 2s ease;
  transition: all 2s ease;
} */

.extensionMidContainerWithScroll .Pane2 {
  height: 40%;
}

.Resizer.horizontal {
  height: 3px;
  margin: -2.5px 0 -3.5px 0;
  cursor: row-resize;
  width: 100%;
  background-color: #000;
  opacity: 0.2;
  min-height: 3px;
}

.Resizer.horizontal:hover {
  background-color: #5f6368;
}

.Resizer.vertical {
  width: 7px;
  margin-right: -4px;
  border-right: 4px solid rgba(255, 255, 255, 0);
  cursor: col-resize;
  border-bottom: 0px;
}

.Resizer.vertical:hover {
  border-right: 4px solid rgba(0, 0, 0, 1);
  width: 7px;
}
.Resizer.disabled {
  cursor: not-allowed;
}
.Resizer.disabled:hover {
  border-color: transparent;
}

/* =========== new design 3 =============== */

.root-container {
  flex-direction: column;
  flex-wrap: unset !important;
  display: flex;
  min-height: calc(100vh - 280px);
  /* background-color: #fff; */
  padding-top: 25px !important;
  padding-bottom: 30px !important;
}

.auth-root {
  /* background-color: rgba(249, 250, 255); */
  min-height: calc(100vh - 280px);
}

.mid-container {
  max-width: 1300px !important;
  width: 100%;
}

.page-header {
  /* color: #4f4f4f; */
  text-align: center;
}

.page-header:first-child,
.page-header > p:first-child {
  font-size: 28px !important;
  text-align: center;
}

.home-container-gray {
  /* background-color: #f1f1f1; */
  min-height: unset;
  padding-bottom: 40px !important;
}

.nd-mobile-container {
  padding: 0px !important;
  padding-top: 0px !important;
  /* background: #fff; */
}

.nd-mobile-container-focused-content {
  padding-top: 0px !important;
}

.home-container-premium {
  min-height: calc(100vh - 60px);
}

.qbp-d-flex {
  display: flex !important;
}

.qbp-pb50 {
  padding-bottom: 50px !important;
}

.p-0 {
  padding: 0 !important;
}

.pl-0 {
  padding-left: 0 !important;
}

.px-0 {
  padding-left: 0 !important;
  padding-right: 0 !important;
}

.m-0 {
  margin: 0 !important;
}

.b-shadow {
  box-shadow: none !important;
}

.w-100 {
  width: 100% !important;
}
/* == start from here === */
.qbp-pb10 {
  padding-bottom: 10px !important;
}

.qbp-pt20 {
  padding-top: 20px !important;
}

.qbp-pb20 {
  padding-bottom: 20px !important;
}

.qbp-textCenter {
  text-align: center !important;
}

.qbp-mx16 {
  margin: 0 16px !important;
}

.qbp-pb20 {
  padding-bottom: 20px !important;
}

.qbp-py20 {
  padding: 20px 0 !important;
}

.qbp-textYellow {
  color: #ffb800;
}

.qbp-semibold {
  font-weight: 600 !important;
}

.qbp-settings-item {
  display: flex;
  padding: 25px 0 15px !important;
  justify-content: space-between;
  border-bottom: 1px solid #8f8f8f;
  color: #000;
  align-items: center;
}

.card-pad {
  padding: 10px 0 1px 0 !important;
}

.qbp-settings-item:last-child {
  border-bottom: 0;
}

.details-subtitle {
  display: inline-block;
  color: rgba(0, 0, 0, 0.6);
  font-weight: normal;
  font-size: 14px !important;
}

.settting-span {
  display: flex;
  align-items: center;
  justify-content: space-between;
}

.details-subtitle-highlight {
  display: inline-block;
  color: rgba(0, 0, 0, 0.6);
  /* font-weight: bold !important; */
  font-size: 14px !important;
}

.premium-container {
  padding-top: 0 !important;
}

/*************************** Login/Sign up popup css ******************************/

.auth-container {
  max-width: 480px;
  width: 100%;

  /* background-color: white; */
  position: relative;
  margin: auto;
  margin-top: 25px;
  margin-bottom: 100px;
}

@media (max-width: 480px) {
  .auth-root {
    padding: 0px 15px;
  }
}

.auth-container-top-border {
  height: 5px;
  width: 100%;
  background: rgb(33, 150, 83);
  background: linear-gradient(90deg, rgba(33, 150, 83, 1) 11.34%, rgba(41, 113, 254, 1) 100%);
}

.social-auth-btn {
  margin: auto !important;
  position: relative;
}

.social-auth-btn img {
  position: absolute;
  left: 15px;
  height: 16px;
}

.auth-btn {
  line-height: 32px !important;
  font-weight: 600 !important;
  font-size: 16px !important;
  height: 45px;
}

.qbp-useraccount-text {
  color: #8a8a8a;
  padding-bottom: 5px;
  font-size: 12px;
}

.qbp-reg-input {
  border: 1px solid #a6a5a5;
  color: #5b5b5b;
  width: 100%;
  display: block;
  float: unset;
  padding: 10px;
  border-radius: 3px;
  margin-bottom: 14px;
  transition: ease all 0.3s;
  height: 45px;
}

.qbp-reg-input:focus {
  box-shadow: 0px 0 16px 0 rgba(0, 0, 0, 0.4);
  outline: none !important;
}

.qbp-error-message {
  font-size: 11px;
  position: absolute;
  bottom: 9px;
  left: 0;
  color: #ee1212;
}

.qbp-error-message1 {
  font-size: 11px;
  padding-bottom: 10px;
  color: #ee1212;
}

.qbp-success-message {
  color: #27b027;
  font-size: 13px;
  line-height: 18px;
  display: flex;
  justify-content: center;
  padding-bottom: 10px;
}

.qbp-prem-input {
  font-weight: normal;
  font-size: 14px;
  color: #151515 !important;
  background-color: #fff;
  width: 100%;
  font-family: arial;
  border: 1px solid #c4c4c4;
  border-radius: 3px;
  height: 40px;
  padding: 0px 15px;
  outline: 0;
}

.login-drawer {
  display: flex;
  padding-top: 8px;
  padding-bottom: 8px;
  flex-direction: column;
  justify-content: flex-start;
}

.style01 {
  font-size: 1.5em;
  font-weight: 600;
  /* color: #fff; */
}

.linkstyle01 {
  color: #fff;
  padding: 0 5px;
  cursor: pointer;
  text-decoration: underline;
}

.flipperTextContainer {
  padding: 0px 32px 0px 15px;
  /* border-left: 1px solid #e0e0e0;*/
  /* color: rgb(0, 0, 0, 0.75); */
}

.flipperTextContainer:hover {
  /* color: black; */
}

.top-tabs .MuiButtonBase-root {
  /* display: inline-block !important; */
  text-transform: capitalize;
  font-size: 1rem;
}

.payment-status {
  font-weight: 600;
  color: #a1a197;
}

/**************************Survey popup css stuff **********************/
.survey-modal {
  background: rgba(0, 0, 0, 0.7);
  position: fixed;
  top: 0;
  left: 0;
  bottom: 0;
  right: 0;
  overflow: auto;
  display: flex;
  min-width: 100vw;
  justify-content: center;
  min-height: 100vh;
  align-items: center;
  z-index: 1201;
}

.survey-container {
  background-color: white;
  max-width: 650px;
  padding: 10px 15px 15px !important;
  margin: auto !important;
  position: relative !important;
}

@media (max-width: 350px) {
  .survey-container {
    margin: auto 12 !important;
  }
}

@media (max-width: 960px) {
  .survey-container {
    max-width: 350px;
  }
}

.survey-header {
  font-size: 20px !important;
  font-weight: 700 !important;
  color: #000 !important;
}

.survey-close-btn {
  position: absolute !important;
  top: 0;
  right: 0;
}

.survey-question {
  font-size: 13px !important;
  padding-bottom: 10px;
}

.so-checkbox-label {
  font-size: 12px !important;
  display: flex;
  padding-bottom: 8px;
  color: #5f6368;
}

.survey-submit-btn {
  color: #2971fe !important;
  font-size: 14px !important;
  float: right;
  font-weight: 500;
  text-transform: uppercase;
}

.unsubscribe-reason {
  width: 100%;
}

.steps {
  font-weight: bold !important;
}

.feedback-textarea {
  width: 100%;
  height: 91px;
  padding: 5px;
  font-size: 0.87rem;
  font-family: 'Open Sans', sans-serif;
}
/* .prompt-container {
  background-color: #fff;
  position: absolute;
  top: 23px;
  z-index: 1150;
  border: 1px solid #bbb;
  border-radius: 2px;
  padding-bottom: 0;
  transition: all 0.15s;

  box-shadow: 0px 1px 1px #999;
} */

/* ============= do not remove this css =============*/
.grecaptcha-badge {
  visibility: hidden;
}
/* =========== do not remove css inside comment area ========== */

/*================== responsive codes ============== */

@media (max-width: 960px) {
  .terms-main-container ol {
    margin: 10px 0px;
    padding-left: 20px;
    word-break: break-word;
  }

  .terms-main-container ol li {
    margin: 10px 0px;
    padding-left: 20px;
    word-break: break-word;
  }
}

.CardElementHolder {
  border: 1px #c4c4c4 solid;
  border-radius: 3px;
  margin-top: 8px;
  padding: 11px 15px 10px;
}

.CardField-child {
  background: #f00 !important;
}

/* ======= new global css start ============= */
p {
  font-size: 16px;
}
a {
  color: #2971fe;
}

.btn-link {
  /* color: #2971fe !important; */
  cursor: pointer;
}
.btn-link:hover {
  text-decoration: underline;
}

.pageTitle {
  font-size: 30px;
  margin: 30px 15px 15px;
  line-height: 41px;
  font-weight: normal;
  text-align: center;
}

.terms-main-container ol li::marker {
  font-size: 16px;
  font-weight: bold;
}
.terms-main-container ol li p b {
  font-weight: 600;
}

/* .CbHosted--focus {
  border: 1px solid #499557 !important;
} */

.chargebee-overwrites::placeholder {
  color: #a0a0a0 !important;
}

.shadow-container {
  height: 6px;
  width: 100%;
  box-shadow: 0px 4px 7px rgba(0, 0, 0, 0.1);
  z-index: 2;
}

input::-webkit-outer-spin-button,
input::-webkit-inner-spin-button {
  -webkit-appearance: none;
  margin: 0;
}

/* Firefox */
input[type='number'] {
  -moz-appearance: textfield;
}

.fix-error {
  background: rgba(73, 149, 87, 0.2) !important;
}

#RESEARCH_EDITOR:before {
  color: #828282;
  margin-left: 60px;
  margin-right: 60px;
  margin: 0 auto;
}

#RESEARCH_EDITOR * {
  max-width: 672px;
  white-space: pre-wrap !important;
}
/* .grammarbot-popover-root {
  pointer-events: none !important;
} */

.page-wrapper {
  padding: var(--main-editor__mce-content-body--padding-y) var(--main-editor__mce-content-body--padding-x);
}

#grammarbot:before {
  color: #828282;
  /* margin-left: 137px;
  margin-right: 138px; */
}

#wordCounterBot:before {
  color: #828282;
}

#grammarbot a {
  color: inherit; /*To add dark mode compatibility */
}

.grammarbot-correction-card-ignore-button {
  padding-top: 13px;
}
.grammarbot-status-icons {
  font-size: 40px !important;
}

.correction-card-wrapper {
  margin-top: -10px;
  padding-top: 8px;
}

.grammarbot-fix-all {
  position: absolute !important;
  top: -48px !important;
  right: 30% !important;
  z-index: 1 !important;
}

.notepadeditor:before {
  color: #828282;
  margin-left: 0px;
}

.notepadeditor {
  width: 100%;
  font-size: 13px !important;
  margin-top: 12px !important;
}

.notepadeditor > p {
  margin-block-start: 0em !important;
  font-size: 13px !important;
}

#main-editor-parent {
  /* ! THESE VARIABLES ARE BEING USED IN SCRIPTS */
  --main-editor__mce-content-body--padding-x: 90px;
  --main-editor__mce-content-body--padding-y: 90px;
}

#main-editor > .mce-content-body {
  /* padding: var(--main-editor__mce-content-body--padding-y, 36px)
    var(--main-editor__mce-content-body--padding-x, 36px); */
  min-height: calc(100vh - 190px);

  /* color: #252525; */
}

#rough-editor {
  width: 100%;
  overflow: auto;
}

#rough-editor > .mce-content-body {
  height: calc(100vh - 122px);
  width: 100%;
  margin: 14px;
  color: #252525;
  overflow: auto;
}

#main-editor > .mce-content-body {
  word-break: break-word !important;
  white-space: pre-wrap !important;
  word-wrap: break-word !important;
}

#main-editor > .mce-content-body > p,
#main-editor > .mce-content-body > .page-wrapper > p {
  font-size: 14px !important;
  font-family: Arial, Helvetica, sans-serif;
  margin: 0px;
}

sup,
sub {
  white-space: pre-wrap !important;
}

.tox-tinymce {
  border: none !important;
  position: absolute !important;
  visibility: visible !important;
  display: block !important;
}

#main-editor .tox-editor-header {
  border: none !important;
  border-bottom: 1px solid !important;
}

#toolbar-location .tox-editor-header {
  border: none !important;
  top: 20px !important;
  left: 14px !important;
}

#toolbar-location .tox-toolbar {
  background: none !important;
}

.tox .tox-toolbar-overlord {
  background: none !important;
}

.tox-notification {
  display: none !important;
}

.tox .tox-tbtn svg {
  fill: #666666 !important;
}

.tox .tox-tbtn--disabled svg,
.tox .tox-tbtn--disabled:hover svg,
.tox .tox-tbtn:disabled svg,
.tox .tox-tbtn:disabled:hover svg {
  fill: rgba(34, 47, 62, 0.5) !important;
}

.tox .tox-tbtn__select-label {
  color: #666666 !important;
}

.tox .tox-autocompleter {
  max-width: 35em !important;
}

.tox .tox-autocompleter .tox-menu {
  max-width: 35em !important;
}

.tox.tox-tinymce--toolbar-sticky-on .tox-editor-header {
  box-shadow: none !important;
}

.tox-editor-header {
  border-right: none !important;
}

.tox-toolbar__primary {
  background: none !important;
  /* box-shadow: 0px 1px 8px 0px rgba(31, 31, 31, 0.15) !important; */
  /* border-bottom: 1px solid #ccc !important; */
  /* border-top: 1px solid #ccc !important; */
  /* padding-left: 15px !important; */
  width: 100% !important;
}

.tox-toolbar__group {
  border: none !important;
  /* box-shadow: 2px -1px 3px -2px rgba(31, 31, 31, 0.15) !important; */
}

.tox-toolbar__group::after {
  content: url('/images/coWriter/line.svg');
}

.tox-toolbar__group:last-child:after {
  content: '';
}

.tox .tox-menu.tox-collection.tox-collection--list {
  width: max-content;
}

.tox-toolbar__primary > .tox-toolbar__group:last-child {
  box-shadow: none !important;
}

.quillSettingSpace {
  -webkit-transition: all 0.1s ease-in-out !important;
  -moz-transition: all 0.1s ease-in-out !important;
  -o-transition: all 0.1s ease-in-out !important;
  transition: all 0.1s ease-in-out !important;
  margin-top: 26px !important;
}

.tox-tbtn,
.tox-tbtn__select-label {
  cursor: pointer !important;
}

.tox-tbtn--disabled {
  cursor: not-allowed !important;
}

@media (max-width: 600px) {
  body {
    margin: 26px 16px 0px 20px;
  }
}

.showFadeEffect {
  --animation-time: 2s;
  animation: opacity-fade var(--animation-time) !important;
}

.dataRefHidden {
  display: none !important;
}

.pulseLoader {
  content: ' ';
  width: 90px;
  height: 12px;
  display: inline-block;
  background-color: #ccc;
  animation: new-animation 1s infinite;
  vertical-align: text-bottom;
  border-radius: 3px;
  margin-left: -5px;
}

@keyframes new-animation {
  0%,
  100% {
    opacity: 1;
  }
  50% {
    opacity: 0.2;
  }
}

@keyframes opacity-fade {
  0% {
    opacity: 0;
  }
  100% {
    opacity: 1;
  }
}

#doc-title {
  padding: 46px 0px 13px 137px;
  width: 70%;
  font-weight: 600;
  font-size: 20px;
}

.mce-content-body[data-mce-placeholder]:not(.mce-visualblocks)::before {
  content: attr(placeholder);
  pointer-events: none;
  display: block; /* For Firefox */
  color: #828282 !important;
}

[contenteditable='true']:empty:before {
  content: attr(placeholder);
  pointer-events: none;
  display: block; /* For Firefox */
  color: #828282 !important;
}

.red-underline {
  border-bottom: #fb3f4b 2px solid;
  transition: all 0.3s ease-in-out;
}

.red-underline:hover {
  background-color: #fb3f4c14;
  border-radius: 2px;
}

.red-underline.error-hovered {
  background-color: #fb3f4c14;
  border-radius: 2px;
  transition: all 0.3s ease-in-out;
  pointer-events: none;
}

.blue-underline {
  border-bottom: #0067c5 2px solid;
  transition: all 0.3s ease-in-out;
}

.blue-underline:hover {
  background-color: #0067c514;
  border-radius: 2px;
}

.blue-underline.error-hovered {
  background-color: #0067c514;
  border-radius: 2px;
  transition: all 0.3s ease-in-out;
  pointer-events: none;
}

.magenta-underline {
  border-bottom: #8051ff 2px solid;
  transition: all 0.3s ease-in-out;
}

.magenta-underline:hover {
  background-color: #8051ff24;
  border-radius: 2px;
}

.magenta-underline.error-hovered {
  background-color: #8051ff24;
  border-radius: 2px;
  transition: all 0.3s ease-in-out;
  pointer-events: none;
}

#fixed-toolbar-container .tox-tinymce-inline .tox-editor-header {
  border: none !important;
}
/*
  Citation Marker style
*/
#main-editor .CitationMarkerStyle {
  padding: 3px;
}

.CitationMarkerStyle_Burst {
  background-color: #ffefde !important;
  color: orange !important;
}

.reduce-margin-block-end {
  margin-block-end: -1em !important;
}

#grammar-checker pre {
  white-space: pre-wrap;
}

#word-counter pre {
  white-space: pre-wrap;
}

.sound-icon {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.sound-wave {
  width: 400px;
  height: 100px;
  display: flex;
  justify-content: space-around;
  align-items: center;
}

.sound-wave .audioOnWithSpeech {
  display: block;
  width: 5px;
  margin-right: 1px;
  height: 90px;
  background: #499557;
  animation: sound 0ms -800ms linear infinite alternate;
  transition: height 0.8s;
}

.sound-wave .audioOff {
  display: block;
  width: 5px;
  margin-right: 0px;
  height: 12px;
  background: #9f9f9f;
}

.sound-wave .audioOnWithoutSpeech {
  display: block;
  width: 5px;
  margin-right: 0px;
  height: 12px;
  background: #499557;
}

@keyframes sound {
  0% {
    opacity: 0.35;
    height: 6px;
  }
  100% {
    opacity: 1;
    height: 46px;
  }
}

@keyframes sound2 {
  0% {
    opacity: 0.35;
    height: 6px;
  }
  100% {
    opacity: 1;
    height: 120px;
  }
}

.audioOnWithSpeech:nth-child(1) {
  height: 2px;
  animation-duration: 274ms;
}

.audioOnWithSpeech:nth-child(2) {
  height: 10px;
  animation-duration: 233ms;
}

.audioOnWithSpeech:nth-child(3) {
  height: 18px;
  animation-duration: 207ms;
}

.audioOnWithSpeech:nth-child(4) {
  height: 26px;
  animation-duration: 258ms;
}

.audioOnWithSpeech:nth-child(5) {
  height: 30px;
  animation-duration: 200ms;
}

.audioOnWithSpeech:nth-child(6) {
  height: 32px;
  animation-duration: 227ms;
}

.audioOnWithSpeech:nth-child(7) {
  height: 34px;
  animation-duration: 241ms;
}

.audioOnWithSpeech:nth-child(8) {
  height: 36px;
  animation-duration: 219ms;
}

.audioOnWithSpeech:nth-child(9) {
  height: 40px;
  animation-duration: 287ms;
}

.audioOnWithSpeech:nth-child(10) {
  height: 46px;
  animation-duration: 242ms;
}

.audioOnWithSpeech:nth-child(11) {
  height: 2px;
  animation-duration: 274ms;
}

.audioOnWithSpeech:nth-child(12) {
  height: 10px;
  animation-duration: 233ms;
}

.audioOnWithSpeech:nth-child(13) {
  height: 18px;
  animation-duration: 207ms;
}

.audioOnWithSpeech:nth-child(14) {
  height: 26px;
  animation-duration: 258ms;
}

.audioOnWithSpeech:nth-child(15) {
  height: 30px;
  animation-duration: 200ms;
}

.audioOnWithSpeech:nth-child(16) {
  height: 32px;
  animation-duration: 227ms;
}

.audioOnWithSpeech:nth-child(17) {
  height: 34px;
  animation-duration: 241ms;
}

.audioOnWithSpeech:nth-child(18) {
  height: 36px;
  animation-duration: 219ms;
}

.audioOnWithSpeech:nth-child(19) {
  height: 40px;
  animation-duration: 287ms;
}

.audioOnWithSpeech:nth-child(20) {
  height: 46px;
  animation-duration: 242ms;
}

.audioOnWithSpeech:nth-child(21) {
  height: 2px;
  animation-duration: 274ms;
}

.audioOnWithSpeech:nth-child(22) {
  height: 10px;
  animation-duration: 233ms;
}

.audioOnWithSpeech:nth-child(23) {
  height: 18px;
  animation-duration: 207ms;
}

.audioOnWithSpeech:nth-child(24) {
  height: 26px;
  animation-duration: 258ms;
}

.audioOnWithSpeech:nth-child(25) {
  height: 30px;
  animation-duration: 200ms;
}

.audioOnWithSpeech:nth-child(26) {
  height: 32px;
  animation-duration: 227ms;
}

.audioOnWithSpeech:nth-child(27) {
  height: 34px;
  animation-duration: 241ms;
}

.mce-content-body [contentEditable='false'][data-mce-selected] {
  cursor: not-allowed;
  outline: 3px solid #f1f1f1 !important;
}

.display--none {
  display: none;
}

/* [title='Font sizes'] {
  width: 65px !important;
} */

.wave .dot {
  display: inline-block;
  width: 4px;
  height: 4px;
  border-radius: 50%;
  /* margin-right: 1px; */
  background: #499557;
  animation: wave 1s linear infinite;
}
.wave .dot:nth-child(1) {
  animation-delay: -0.9s;
}
.wave .dot:nth-child(2) {
  animation-delay: -0.7s;
}
.wave .dot:nth-child(3) {
  animation-delay: -0.5s;
}

@keyframes wave {
  0%,
  60%,
  100% {
    transform: initial;
  }
  30% {
    transform: translateY(-4px);
  }
}

    button {
      font-size: 12px;
    }
    p { 
      color: black; 
      font-size: 12px; 
    }
    input {
      color: black; 
      font-size: 12px; 
      background: white;
    }
    textarea {
      color: black; 
      font-size: 12px; 
    }
    checkbox {
      background: white;
    }
    </style><style><style data-emotion="extn-css" data-s=""></style></style></template></quillbot-extension-root><grammarly-desktop-integration data-grammarly-shadow-root="true"><template shadowrootmode="open"><style>
  div.grammarly-desktop-integration {
    position: absolute;
    width: 1px;
    height: 1px;
    padding: 0;
    margin: -1px;
    overflow: hidden;
    clip: rect(0, 0, 0, 0);
    white-space: nowrap;
    border: 0;
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select:none;
    user-select:none;
  }

  div.grammarly-desktop-integration:before {
    content: attr(data-content);
  }
</style><div aria-label="grammarly-integration" role="group" tabindex="-1" class="grammarly-desktop-integration" data-content="{&quot;mode&quot;:&quot;full&quot;,&quot;isActive&quot;:true,&quot;isUserDisabled&quot;:false}"></div></template></grammarly-desktop-integration><iframe sandbox="allow-scripts allow-same-origin" id="6087fd6acb7bee8" frameborder="0" allowtransparency="true" marginheight="0" marginwidth="0" width="0" hspace="0" vspace="0" height="0" style="height:0px;width:0px;display:none;" scrolling="no" src="./fibonacci_recurssion_files/usync.html">
    </iframe><iframe sandbox="allow-scripts allow-same-origin" id="61362e52c6b09a7" frameborder="0" allowtransparency="true" marginheight="0" marginwidth="0" width="0" hspace="0" vspace="0" height="0" style="height:0px;width:0px;display:none;" scrolling="no" src="./fibonacci_recurssion_files/user_sync.html">
    </iframe><iframe sandbox="allow-scripts allow-same-origin" id="62e9f46ab04e14b" frameborder="0" allowtransparency="true" marginheight="0" marginwidth="0" width="0" hspace="0" vspace="0" height="0" style="height:0px;width:0px;display:none;" scrolling="no" src="./fibonacci_recurssion_files/ixmatch.html">
    </iframe><iframe sandbox="allow-scripts allow-same-origin" id="632384b5f8bdc4b" frameborder="0" allowtransparency="true" marginheight="0" marginwidth="0" width="0" hspace="0" vspace="0" height="0" style="height:0px;width:0px;display:none;" scrolling="no" src="./fibonacci_recurssion_files/async_usersync.html">
    </iframe><iframe sandbox="allow-scripts allow-same-origin" id="64a0711ad403415" frameborder="0" allowtransparency="true" marginheight="0" marginwidth="0" width="0" hspace="0" vspace="0" height="0" style="height:0px;width:0px;display:none;" scrolling="no" src="./fibonacci_recurssion_files/sync.html">
    </iframe></html>
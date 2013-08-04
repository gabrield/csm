              
$(document).ready ->
    if not ('webkitGetUserMedia' of navigator or 'getUserMedia' of navigator)
        $('#old-browser-dialog').dialog
            title: 'Update your browser'
            modal: yes
            buttons:
              ok: -> document.location.href = 'http://google.com/chrome'
    else
      CSM.main_window_view = new CSM.MainWindowView el: $ '#main-window'
      CSM.toolbar_view = new CSM.ToolbarView el: $ '#toolbar-view'
      CSM.camera_view = new CSM.CameraView el: $ '#camera-view'
      CSM.last_frame_view = new CSM.LastFrameView el: $ '#last-frame-view'
      CSM.EmptyFrame = CSM.EmptyFrame
      CSM.framebar_view = new CSM.FramebarView el: $ '#framebar-view'
    
    

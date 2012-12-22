              
$(document).ready ->
    if not ('webkitGetUserMedia' of navigator or 'getUserMedia' of navigator)
        $('#old-browser-dialog').dialog
            title: 'Update your browser'
            modal: yes
            buttons:
              ok: -> document.location.href = 'http://google.com/chrome'
    else
      window.main_window_view = new MainWindowView el: $ '#main-window'
      window.toolbar_view = new ToolbarView el: $ '#toolbar-view'
      window.camera_view = new CameraView el: $ '#camera-view'
      window.last_frame_view = new LastFrameView el: $ '#last-frame-view'
      window.EmptyFrame = EmptyFrame
      window.framebar_view = new FramebarView el: $ '#framebar-view'
    
    
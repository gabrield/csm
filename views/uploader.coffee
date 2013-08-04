class CSM.Uploader
    save_images:(callback) ->
        _.each CSM.framebar_view.frames, (frame) =>
            $.post "/#{CSM.session_id()}/save/",
                file: frame.src
                image_id: frame.sequence_number(),
            
        callback()
    
    finished: ->
        $.post "/#{CSM.session_id()}/finished/", =>
            @wait_for_encoding_complete()
        
    wait_for_encoding_complete: ->
        $.get "/#{CSM.session_id()}/is_video_ready/", (data) =>
            is_video_ready = false
            is_video_ready = true if data == 'true'
            
            if is_video_ready
                $('#finished-dialog').dialog 'close'
                document.location.href = "/#{CSM.session_id()}/download/"
            else
                setTimeout =>
                    @wait_for_encoding_complete()
                , 2000
                
    
$(document).ready ->
    CSM.session_id = ->
        session_id = 'xxxxxxxxx'.replace /[x]/g , ->
            _.random 9
        
        CSM.session_id = ->
            session_id
        
        session_id
        
    CSM.uploader = new CSM.Uploader

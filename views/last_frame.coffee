class CSM.LastFrameView extends Backbone.View
    initialize: ->
        @camera = CSM.camera_view
        @bind 'render', @render
        @image = @$el.find 'img'
        
    render: -> 
        canvas = @camera.canvas[0]
        video = @camera.video[0]

        canvas.width = video.videoWidth
        canvas.height = video.videoHeight
        @image.width video.videoWidth
        @image.height video.videoHeight
        
        context = canvas.getContext '2d'
        context.drawImage video, 0, 0
        @image.attr 'src', canvas.toDataURL 'image/webp 1'
        CSM.framebar_view.add_frame @image
                
    preview: ->
        first_frame = CSM.framebar_view.get_first_frame()
        @show_frame first_frame
        if (first_frame.has_next())
            @timer_show first_frame.next()
        
    timer_show: (frame) ->
        setTimeout =>
            @show_frame frame
            if (frame.has_next())
                @timer_show frame.next()
        , 1000/25
        
    show_frame: (frame) ->
        @image.attr 'src', frame.src

class CSM.FramebarView extends Backbone.View
    frames: []

    render: ->
        @$el.find('ul').sortable(placeholder: "ui-state-highlight").disableSelection()
        @$el.animate scrollTop: @$el.find('img:last').offset().top, 'slow'
    
    add_frame: ($image) ->
        new_frame = new CSM.EmptyFrame()
        new_frame.framebar = @
        new_frame.from_image $image

        new_frame.set_el $("<li>#{new_frame.render()}</li>").appendTo @$el.find('ul')
        
        @frames.push new_frame
        @render()
        
    is_last_frame: (frame) ->
        frame.sequence_number() == _.size(@frames)
        
    get_first_frame: ->
        _.first @frames

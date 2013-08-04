class CSM.FramebarView extends Backbone.View
    frames: []

    render: ->
        @$el.find('ul').sortable(placeholder: "ui-state-highlight").disableSelection()
        @$el.animate scrollTop: @$el.find('img:last').offset().top, 'slow'
    
    add_frame: ($image) ->
        new_frame = new CSM.EmptyFrame()
        new_frame.from_image $image
        
        if not (_.isEmpty @frames)
            _.last(@frames).notify_of_sibling new_frame
        
        new_frame.set_el $("<li>#{new_frame.render()}</li>").appendTo @$el.find('ul')
        
        @frames.push new_frame
        @render()
        
    get_first_frame: ->
        _.first @frames

class CSM.EmptyFrame

    sequence_number: -> 
        $el.index()

    constructor: ->
        true
        
    from_image: ($image) ->
        @src = $image.attr 'src'
        
    has_next: ->
        not @framebar.is_last_frame @
    
    next: ->
        @framebar.frames[@sequence_number()]
            
    set_el: (el) ->
        @$el =$(el)
        @bind_events()
        
    bind_events: ->
        @$el.on 'click', =>
            @click()
        
    render: ->
        "<img src='#{@src}'>"
        
    click: ->
        CSM.last_frame_view.show_frame this
        
        

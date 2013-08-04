class CSM.EmptyFrame
    constructor: ->
        true
        
    from_image: ($image) ->
        @src = $image.attr 'src'
        
    has_next: ->
        no
    
    next: ->
        off
    
    notify_of_sibling: (sibling) ->
        @has_next = ->
            yes
            
        @next = ->
            sibling
            
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
        
        

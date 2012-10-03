(function() {
  var CameraView, FramebarView, LastFrameView, MainWindowView, ToolbarView,
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  MainWindowView = (function(_super) {

    __extends(MainWindowView, _super);

    function MainWindowView() {
      MainWindowView.__super__.constructor.apply(this, arguments);
    }

    MainWindowView.prototype.initialize = function() {
      this.$el.sortable({
        items: "li:not(.toolbar)",
        placeholder: "ui-state-highlight"
      }).disableSelection();
      return this.$el.bind('sortupdate', function(event, ui) {
        if (!_.any($(ui.item[0]).parents('li'), function(el) {
          return $(el).is('.toolbar');
        })) {
          return window.camera_view.trigger('render');
        }
      });
    };

    return MainWindowView;

  })(Backbone.View);

  ToolbarView = (function(_super) {

    __extends(ToolbarView, _super);

    function ToolbarView() {
      ToolbarView.__super__.constructor.apply(this, arguments);
    }

    ToolbarView.prototype.events = {
      'click button#shot': 'shot'
    };

    ToolbarView.prototype.initialize = function() {
      return this.$el.find('button').button();
    };

    ToolbarView.prototype.shot = function() {
      return window.last_frame_view.trigger('render');
    };

    return ToolbarView;

  })(Backbone.View);

  CameraView = (function(_super) {

    __extends(CameraView, _super);

    function CameraView() {
      CameraView.__super__.constructor.apply(this, arguments);
    }

    CameraView.prototype.initialize = function() {
      this.canvas = this.$el.find('canvas');
      this.video = this.$el.find('video');
      this.bind('render', this.render);
      return this.render();
    };

    CameraView.prototype.render = function() {
      var _this = this;
      return navigator.webkitGetUserMedia('video', function(stream) {
        stream = window.webkitURL.createObjectURL(stream);
        return _this.video.attr('src', stream);
      }, function(exception) {
        return console.log(exception);
      });
    };

    return CameraView;

  })(Backbone.View);

  LastFrameView = (function(_super) {

    __extends(LastFrameView, _super);

    function LastFrameView() {
      LastFrameView.__super__.constructor.apply(this, arguments);
    }

    LastFrameView.prototype.initialize = function() {
      this.camera = window.camera_view;
      return this.bind('render', this.render);
    };

    LastFrameView.prototype.render = function() {
      var canvas, context, image, video;
      canvas = this.camera.canvas[0];
      video = this.camera.video[0];
      context = canvas.getContext('2d');
      context.drawImage(video, 0, 0);
      image = this.$el.find('img');
      image.attr('src', canvas.toDataURL('image/jpeg'));
      return window.framebar_view.addFrame(image);
    };

    return LastFrameView;

  })(Backbone.View);

  FramebarView = (function(_super) {

    __extends(FramebarView, _super);

    function FramebarView() {
      FramebarView.__super__.constructor.apply(this, arguments);
    }

    FramebarView.prototype.render = function() {
      this.$el.find('ul').sortable({
        placeholder: "ui-state-highlight"
      }).disableSelection();
      return this.$el.animate({
        scrollTop: this.$el.find('img:last').offset().top
      }, 'slow');
    };

    FramebarView.prototype.addFrame = function($image) {
      var html;
      html = $image[0].outerHTML;
      this.$el.find('ul').append("<li>" + html + "</li>");
      return this.render();
    };

    return FramebarView;

  })(Backbone.View);

  $(document).ready(function() {
    if (!('webkitGetUserMedia' in navigator || 'getUserMedia' in navigator)) {
      return $('#old-browser-dialog').dialog({
        title: 'Update your browser',
        modal: true,
        buttons: {
          ok: function() {
            return document.location.href = 'http://google.com/chrome';
          }
        }
      });
    } else {
      new MainWindowView({
        el: $('#main-window')
      });
      new ToolbarView({
        el: $('#toolbar-view')
      });
      window.camera_view = new CameraView({
        el: $('#camera-view')
      });
      window.last_frame_view = new LastFrameView({
        el: $('#last-frame-view')
      });
      return window.framebar_view = new FramebarView({
        el: $('#framebar-view')
      });
    }
  });

}).call(this);

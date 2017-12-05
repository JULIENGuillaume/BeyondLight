document.getElementById("left-menu").onclick = function(e) {onLeftMenuClick(e)};
function onLeftMenuClick(e) {
    var request_id = window.cefQuery({
        request: 'index-' + e.target.id,
        persistent: false,
        onSuccess: function(response) {},
        onFailure: function(error_code, error_message) {
            console.log("failed to go to menu entry: " + e.target.id)
        }
    });
    window.cefQueryCancel(request_id);

}
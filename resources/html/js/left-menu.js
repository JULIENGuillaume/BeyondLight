document.getElementById("left-menu").onclick = function(e) {onLeftMenuClick(e)};
function onLeftMenuClick(e) {
    window.cefQuery({
        request: 'index-' + e.target.id,
        onSuccess: function(response) {},
        onFailure: function(error_code, error_message) {
            console.log("failed to go to menu entry: " + e.target.id)
        }
    });
}
var _Utils = function ()
{
    this.findChildById = function (element, childID, isSearchInnerDescendant) // isSearchInnerDescendant <= true for search in inner childern
    {
        var retElement = null;
        var lstChildren = isSearchInnerDescendant ? Utils.getAllDescendant(element) : element.childNodes;

        for (var i = 0; i < lstChildren.length; i++)
        {
            if (lstChildren[i].id == childID)
            {
                retElement = lstChildren[i];
                break;
            }
        }

        return retElement;
    }

    this.getAllDescendant = function (element, lstChildrenNodes)
    {
        lstChildrenNodes = lstChildrenNodes ? lstChildrenNodes : [];

        var lstChildren = element.childNodes;

        for (var i = 0; i < lstChildren.length; i++)
        {
            if (lstChildren[i].nodeType == 1) // 1 is 'ELEMENT_NODE'
            {
                lstChildrenNodes.push(lstChildren[i]);
                lstChildrenNodes = Utils.getAllDescendant(lstChildren[i], lstChildrenNodes);
            }
        }

        return lstChildrenNodes;
    }
}
var Utils = new _Utils;
/** \file
 *  Game Develop
 *  2008-2014 Florian Rival (Florian.Rival@gmail.com)
 */
#ifndef INITIALINSTANCESPROPGRIDHELPER_H
#define INITIALINSTANCESPROPGRIDHELPER_H
#include <wx/propgrid/propgrid.h>
#include <vector>
#include <wx/propgrid/propgrid.h>
namespace gd { class InitialInstance; }
namespace gd { class Project; }
namespace gd { class Layout; }

namespace gd
{

/**
 * \brief Helper class used to easily use a wxPropertyGrid so as to view and edit the properties of
 * the gd::InitialInstance selected in a gd::LayoutEditorCanvas.
 *
 * Usage example :
 * \code
class MyEditor
{
    MyEditor(gd::Project & project_, gd::Layout & layout_) :
        instanceHelper(project_, layout_),
        project(project_),
        layout(layout_)
    {
        grid = new wxPropertyGrid(this,ID_PROPGRID,wxDefaultPosition,wxSize(359,438),0,_T("ID_PROPGRID"));
        instanceHelper.SetGrid(grid);
        Connect(ID_PROPGRID, wxEVT_PG_SELECTED, (wxObjectEventFunction)&MyEditor::OnPropertySelected);
        Connect(ID_PROPGRID, wxEVT_PG_CHANGED, (wxObjectEventFunction)&MyEditor::OnPropertyChanged);
    }

    OnPropertySelected(wxPropertyGridEvent & event)
    {
        instanceHelper.OnPropertySelected(selection, event);
    }

    OnPropertyChanged(wxPropertyGridEvent & event)
    {
        instanceHelper.OnPropertyChanged(selection, event);
    }

    Refresh()
    {
        instanceHelper.RefreshFrom(selection);
    }
private:
    wxPropertyGrid * grid;
    gd::Project & project;
    gd::Layout & layout;
    InitialInstancesPropgridHelper instanceHelper;
};
 * \endcode
 *
 * \see gd::InitialInstance
 * \see gd::LayoutEditorCanvas
 *
 * \ingroup IDEdialogs
 */
class GD_CORE_API InitialInstancesPropgridHelper
{
public:

    /**
     * \brief Default constructor.
     * \param grid A pointer to the wxPropertyGrid to be used.
     * \param project The project edited
     * \param layout The layout being edited
     */
    InitialInstancesPropgridHelper(gd::Project & project_, gd::Layout & layout_) : grid(NULL), project(project_), layout(layout_) {};
    virtual ~InitialInstancesPropgridHelper() {};

    /**
     * \brief Refresh the property grid from a list of initial instances ( For example, the selection of a gd::LayoutEditorCanvas )
     * \param selectedInitialInstances The initial instances which are to be displayed ( For example, the selection of a gd::LayoutEditorCanvas ).
     */
    void RefreshFrom(const std::vector<gd::InitialInstance*> & selectedInitialInstances);

    /**
     * \brief Call this when the event wxEVT_PG_SELECTED of wxPropertyGrid is triggered.
     * \param selectedInitialInstances The initial instances which are displayed ( For example, the selection of a gd::LayoutEditorCanvas ).
     * \param event The event generated by wxWidgets.
     */
    void OnPropertySelected(const std::vector<gd::InitialInstance*> & selectedInitialInstances, wxPropertyGridEvent& event);

    /**
     * \brief Call this when the event wxEVT_PG_CHANGED of wxPropertyGrid is triggered.
     * \param selectedInitialInstances The initial instances which are displayed ( For example, the selection of a gd::LayoutEditorCanvas ).
     * \param event The event generated by wxWidgets.
     */
    void OnPropertyChanged(const std::vector<gd::InitialInstance*> & selectedInitialInstances, wxPropertyGridEvent& event);

    /**
     * \brief Set the grid being used.
     */
    void SetGrid(wxPropertyGrid * grid_) { grid = grid_; }

private:
    wxPropertyGrid * grid; ///< The grid used for diplaying and editing properties.
    gd::Project & project;
    gd::Layout & layout;
};

}

#endif // INITIALINSTANCESPROPGRIDHELPER_H

# In order to compile your task in O2Physics

Put your task in the `O2Physics/ALICE3/Tasks/` folder
Add your task to `O2Physics/ALICE3/Tasks/CMakeLists.txt` e.g.:

```
o2physics_add_dpl_workflow(alice3-example-task
                    SOURCES alice3ExampleTask.cxx
                    PUBLIC_LINK_LIBRARIES O2Physics::AnalysisCore O2::DCAFitter
                    COMPONENT_NAME AnalysisTutorial)
```
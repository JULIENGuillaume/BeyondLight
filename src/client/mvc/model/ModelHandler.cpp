//
// Created by diguie_t on 11/26/2017.
//

#include "ModelHandler.hh"

ModelHandler::ModelHandler() { // todo pass network handler so models can query for updates or send changes
    this->_data = {
            //{"student", std::shared_ptr<ABaseModel>(new StudentModel())}
    };
}
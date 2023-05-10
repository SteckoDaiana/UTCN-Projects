import { useState } from "react";
import * as React from "react";
import deviceService from "../../services/deviceService";

export default function CreateDevice() {
  const [id_item, setId] = useState("");
  const [description, setDescription] = useState("");
  const [adress, setAdress] = useState("");
  const [consumption, setConsumption] = useState("");
  const goToAdminPage = () => {
    window.location.href = "admin-page";
  };
  const initValues = {
    id_item: "",
    description: "",
    adress: "",
    consumption: "",
  };
  const insertDevice = () => {
    initValues.id_item = id_item;
    initValues.description = description;
    initValues.adress = adress;
    initValues.consumption = consumption;

    console.log(initValues);
    deviceService.updateProsumer(initValues);
  };

  const changeHandler = (event) => {
    setId(event.target.value);
  };

  const changeHandler1 = (event) => {
    setDescription(event.target.value);
  };

  const changeHandler2 = (event) => {
    setAdress(event.target.value);
  };
  const changeHandler3 = (event) => {
    setConsumption(event.target.value);
  };

  return (
    <div className="w-75%">
      <div className=" font-extrabold text-gray-900">
        <div>
          <h1>Device Id: </h1>
          <input name="id_item" onChange={(event) => changeHandler(event)} />
        </div>
        <div>
          <h1>Description: </h1>
          <input
            name="description"
            onChange={(event) => changeHandler1(event)}
          />
        </div>
        <div>
          <h1>Adress: </h1>
          <input name="adress" onChange={(event) => changeHandler2(event)} />
        </div>
        <div>
          <h1>Consumption: </h1>
          <input
            name="consumption"
            onChange={(event) => changeHandler3(event)}
          />
        </div>

        <div>
          <button className="insertBtn" onClick={insertDevice}>
            Update Device
          </button>
        </div>
        <div>
          <button className="backBtn" onClick={goToAdminPage}>
            Go back
          </button>
        </div>
      </div>
    </div>
  );
}

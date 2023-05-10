import React, { useEffect, useState } from "react";
import deviceService from "../services/deviceService";
import measurementsService from "../services/measurementsService";
import "./ViewDevicePage.css";
import LoginPage from "./Login";

function ViewDeviceForClientPage() {
  const [allDevices, setDevices] = useState([]);
  useEffect(() => {
    getDevices();
  }, []);
  const [allMeasurements, setMeasurements] = useState([]);
  useEffect(() => {
    getMeasurementss();
  }, []);
  const goToClientPage = () => {
    window.location.href = "client-page";
  };

  async function getDevices() {
    let datas = await deviceService.getItems();
    setDevices(datas.data);
    console.log(datas.data);
  }

  async function getMeasurementss() {
    let datam = await measurementsService.getMeasurements();
    setMeasurements(datam.data);
    console.log(datam.data);
  }

  return (
    <div>
      <div>
        <table className="table">
          <thead>
            <tr>
              <th>id_item</th>
              <th>Description</th>
              <th>Adress</th>
              <th>Consumption</th>
              <th>Username</th>
            </tr>
          </thead>
          <tbody>
            {allDevices.map((data) => {
              return (
                <tr key={data.id_item}>
                  <td>{data.id_item}</td>
                  <td>{data.description}</td>
                  <td>{data.adress}</td>
                  <td>{data.consumption}</td>
                  <td>{data.username}</td>
                </tr>
              );
            })}
          </tbody>
        </table>

        <div>
          <table className="table-measurements">
            <thead>
              <tr>
                <th>item_id</th>
                <th>consumption</th>
                <th>timestamp</th>
              </tr>
            </thead>
            <tbody>
              {allMeasurements.map((dataa) => {
                return (
                  <tr key={dataa.id}>
                    <td>{dataa.id}</td>
                    <td>{dataa.consumption}</td>
                    <td>{dataa.timestamp}</td>
                  </tr>
                );
              })}
            </tbody>
          </table>
        </div>

        <div>
          <button className="backBtn" onClick={goToClientPage}>
            Go back
          </button>
        </div>
      </div>
    </div>
  );
}
export default sessionStorage.getItem("clientUID")
  ? ViewDeviceForClientPage
  : LoginPage;

import React, { useEffect, useState } from "react";
import deviceService from "../services/deviceService";
import "./ViewDevicePage.css";
import LoginPage from "./Login";

function ViewDevicePage() {
  const [allDevices, setDevices] = useState([]);
  useEffect(() => {
    getDevices();
  }, []);
  const goToAdminPage = () => {
    window.location.href = "admin-page";
  };

  async function getDevices() {
    let datas = await deviceService.getItems();
    setDevices(datas.data);
    console.log(datas.data);
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
          <button className="backBtn" onClick={goToAdminPage}>
            Go back
          </button>
        </div>
      </div>
    </div>
  );
}
export default sessionStorage.getItem("admUID") ? ViewDevicePage : LoginPage;

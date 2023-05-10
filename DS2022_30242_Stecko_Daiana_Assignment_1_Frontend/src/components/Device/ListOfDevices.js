import React, { Component, useEffect } from "react";
import deviceService from "../../services/deviceService";

const adminUrl = "http://localhost:8080/device";

class ListOfDevices extends Component {
  constructor(props) {
    super(props);

    this.state = {
      devices: [],
    };
    this.addDevice = this.addDevice.bind(this);
    this.updateDevice = this.updateDevice.bind(this);
    this.deleteDevice = this.deleteDevice.bind(this);
  }

  addDevice() {
    this.props.history.push(`${adminUrl}`);
  }
}

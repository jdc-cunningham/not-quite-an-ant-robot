import React, { useEffect, useState } from 'react';
import './App.scss';
import Telemetry from './components/telemetry/Telemetry';
import Display from './components/display/Display';
import DirectionalPad from './components/directional-pad/DirectionalPad';

function App() {
  const [socket, setSocket] = useState(null);

  const connectToEspSocket = () => {
    const espSocket = new WebSocket("ws://192.168.1.181:80");

    espSocket.onopen = (event) => {
      setSocket(espSocket);
    };

    espSocket.onmessage = (event) => {
      console.log(event);
    };
  }

  useEffect(() => {
    console.log('run socket');
    if (!socket) {
      connectToEspSocket();
    }
  }, [socket]);

  return (
    <div className="MobileController">
      {/* see concept here controller/reactjs/controller/src/concept.PNG */}
      <Telemetry />
      <Display />
      <DirectionalPad socket={socket} />
    </div>
  );
}

export default App;

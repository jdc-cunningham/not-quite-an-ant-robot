import React, { useState, useEffect } from 'react';
import './DirectionalPad.scss';

const DirectionalPad = (props) => {
  const { socket } = props;

  const [activeDirection, setActiveDirection] = useState(null);
  const [motionInterval, setMotionInterval] = useState(null);

  const dPadClick = (direction) => {
    if (direction === activeDirection) {
      setActiveDirection(null);
    } else {
      setActiveDirection(direction);
    }
  };

  useEffect(() => {
    clearInterval(motionInterval);
    if (activeDirection && socket) {
      socket.send(activeDirection);
      setMotionInterval(
        setInterval(() => {
          socket.send(activeDirection);
        }, 1000)
      );
    }
  }, [activeDirection]);

  useEffect(() => {
    console.log('socket', socket);
  }, [socket]);

  return (
    <div className="MobileController__directional-pad cmd-up">
      <div
        className={ `directional-pad___arrow up ${activeDirection == "F" ? "active" : ""}` }
        onClick={ () => dPadClick("F") }></div>
      <div
        className={ `directional-pad___arrow right ${activeDirection == "R" ? "active" : ""}` }
        onClick={ () => dPadClick("R") }></div>
      <div
        className={ `directional-pad___arrow down ${activeDirection == "B" ? "active" : ""}` }
        onClick={ () => dPadClick("B") }></div>
      <div
        className={ `directional-pad___arrow left ${activeDirection == "L" ? "active" : ""}` }
        onClick={ () => dPadClick("L") }></div>
      <div
        className={ `directional-pad___center-pad` }></div>
    </div>
  );
}

export default DirectionalPad;
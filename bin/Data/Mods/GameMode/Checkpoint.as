// Rotator script object class. Script objects to be added to a scene node must implement the empty ScriptObject interface
class Checkpoint : ScriptObject
{
    Vector3 scale;

    void Start()
    {
        // Subscribe physics collisions that concern this scene node
        SubscribeToEvent(node, "NodeCollisionStart", "HandleNodeCollision");
        scale = node.scale;
    }

    void HandleNodeCollision(StringHash eventType, VariantMap& eventData)
    {
        // Get the other colliding body, make sure it is moving (has nonzero mass)
        RigidBody@ otherBody = eventData["OtherBody"].GetPtr();

        if (otherBody.mass > 0.0f)
        {
            if (otherBody.node.vars.Contains("Player")) {
                VariantMap data;
                // int playerId = otherBody.node.vars["Player"].GetInt();
                data["Score"] = 5;
                // data["Player"] = playerId;
                // SendEvent("CheckpointReached", data);
                log.Info("Adding score");
                otherBody.node.SendEvent("PlayerScoreAdd", data);


                data["Type"] = SOUND_EFFECT;
                data["SoundFile"] = "Data/Sounds/checkpoint.wav";
                SendEvent("PlaySound", data);

                // node.Remove();
            }
        }
    }

    // Update is called during the variable timestep scene update
    void Update(float timeStep)
    {
        node.Rotate(Quaternion(0, timeStep * 10, 0));
        Vector3 newScale = scale + scale * Sin(time.elapsedTime * 200.0f) * 0.1f;
        newScale.y = scale.y;
        node.scale = newScale;
    }
}

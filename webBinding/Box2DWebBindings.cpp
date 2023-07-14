        #include <box2d.h>

        #include <emscripten.h>
        #include <emscripten/bind.h>

        using namespace emscripten;

        // static void setShape(b2FixtureDef* f, const b2Shape* shape) {
        //         f->shape = shape;
        // }

        // static const b2Shape* getShape(b2FixtureDef* f) {
        //         return f->shape;
        // }

        // static float b2Vec2GetX(b2Vec2* v) {
        //         return v->x;
        // }
        // static void b2Vec2SetX(b2Vec2* v, float in) {
        //         v->x = in;
        // }
        
        struct b2RayCastCallbackWrapper : public wrapper<b2RayCastCallback> {
                EMSCRIPTEN_WRAPPER(b2RayCastCallbackWrapper)
                float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override {
                        return call<float>("ReportFixture", fixture, point, normal, fraction);
                }
        };

        //----------------------------------------------------------------------------------------------------------------------
        EMSCRIPTEN_BINDINGS(b2) {
        //     value_object<b2Vec2>("Vec2")
        //             .field("x", &b2Vec2::x)
        //             .field("y", &b2Vec2::y);
        value_object<b2Vec3>("Vec3")
                .field("x", &b2Vec3::x)
                .field("y", &b2Vec3::y)
                .field("z", &b2Vec3::z);
        value_object<b2Mat22>("Mat22")
                .field("ex", &b2Mat22::ex)
                .field("ey", &b2Mat22::ey);
        value_object<b2Mat33>("Mat33")
                .field("ex", &b2Mat33::ex)
                .field("ey", &b2Mat33::ey)
                .field("ez", &b2Mat33::ez); 
        value_object<b2Rot>("Rot")
                .field("s", &b2Rot::s)
                .field("c", &b2Rot::c);
        value_object<b2Transform>("Transform")
                .field("p", &b2Transform::p)
                .field("q", &b2Transform::q);
        value_object<b2Sweep>("Sweep")
                .field("localCenter", &b2Sweep::localCenter)
                .field("c0", &b2Sweep::c0)
                .field("c", &b2Sweep::c)
                .field("a0", &b2Sweep::a0)
                .field("a", &b2Sweep::a)
                .field("alpha0", &b2Sweep::alpha0);
        value_object<b2Color>("Color")
                .field("r", &b2Color::r)
                .field("g", &b2Color::g)
                .field("b", &b2Color::b);
        value_object<b2ContactFeature>("ContactFeature")
                .field("indexA", &b2ContactFeature::indexA)
                .field("indexB", &b2ContactFeature::indexB)
                .field("typeA", &b2ContactFeature::typeA)
                .field("typeB", &b2ContactFeature::typeB);
        value_object<b2ContactID>("ContactID")
                .field("cf", &b2ContactID::cf)
                .field("key", &b2ContactID::key);
        value_object<b2ManifoldPoint>("ManifoldPoint")
                .field("localPoint", &b2ManifoldPoint::localPoint)
                .field("normalImpulse", &b2ManifoldPoint::normalImpulse)
                .field("tangentImpulse", &b2ManifoldPoint::tangentImpulse)
                .field("id", &b2ManifoldPoint::id);
        value_object<b2Manifold>("Manifold")
                .field("points", &b2Manifold::points)
                .field("localNormal", &b2Manifold::localNormal)
                .field("localPoint", &b2Manifold::localPoint)
                .field("type", &b2Manifold::type)
                .field("pointCount", &b2Manifold::pointCount);
        value_object<b2WorldManifold>("WorldManifold")
                .field("normal", &b2WorldManifold::normal)
                .field("points", &b2WorldManifold::points)
                .field("separations", &b2WorldManifold::separations);
        value_object<b2ClipVertex>("ClipVertex")
                .field("v", &b2ClipVertex::v)
                .field("id", &b2ClipVertex::id);
        value_object<b2RayCastInput>("RayCastInput")
                .field("p1", &b2RayCastInput::p1)
                .field("p2", &b2RayCastInput::p2)
                .field("maxFraction", &b2RayCastInput::maxFraction);
        value_object<b2RayCastOutput>("RayCastOutput")
                .field("normal", &b2RayCastOutput::normal)
                .field("fraction", &b2RayCastOutput::fraction);
        value_object<b2AABB>("AABB")
                .field("lowerBound", &b2AABB::lowerBound)
                .field("upperBound", &b2AABB::upperBound);
        value_object<b2MassData>("MassData")
                .field("mass", &b2MassData::mass)
                .field("center", &b2MassData::center)
                .field("I", &b2MassData::I);
        // value_object<b2Shape::Type>("ShapeType")
        //         .field("e_circle", &b2Shape::e_circle)
        //         .field("e_edge", &b2Shape::e_edge)
        //         .field("e_polygon", &b2Shape::e_polygon)
        //         .field("e_chain", &b2Shape::e_chain)
        //         .field("e_typeCount", &b2Shape::e_typeCount);
        value_object<b2Filter>("Filter")
                .field("categoryBits", &b2Filter::categoryBits)
                .field("maskBits", &b2Filter::maskBits)
                .field("groupIndex", &b2Filter::groupIndex);
        value_object<b2ContactImpulse>("ContactImpulse")
                .field("normalImpulses", &b2ContactImpulse::normalImpulses)
                .field("tangentImpulses", &b2ContactImpulse::tangentImpulses)
                .field("count", &b2ContactImpulse::count);

        //b2_maxPolygonVertices

        //binding class b2Vec2
        class_<b2Vec2>("Vec2")
                .constructor<>()
                .constructor<float, float>()
                // .property("x", &b2Vec2::GetX, &b2Vec2::SetX)
                // .property("y", &b2Vec2::GetY, &b2Vec2::SetY)
                .function("SetX", &b2Vec2::SetX)
                .function("GetX", &b2Vec2::GetX)
                .function("SetY", &b2Vec2::SetY)
                .function("GetY", &b2Vec2::GetY)
                .function("SetZero", &b2Vec2::SetZero)
                .function("Set", &b2Vec2::Set)
                .function("Length", &b2Vec2::Length)
                .function("LengthSquared", &b2Vec2::LengthSquared)
                .function("Normalize", &b2Vec2::Normalize)
                .function("IsValid", &b2Vec2::IsValid);



        //binding class b2QueryCallback
        class_<b2QueryCallback>("QueryCallback")
                .function("ReportFixture", &b2QueryCallback::ReportFixture, allow_raw_pointers());

        // //binding class b2RayCastCallback
        // class_<b2RayCastCallback>("RayCastCallback")
        //         .function("ReportFixture", &b2RayCastCallback::ReportFixture, allow_raw_pointers());

        // override b2RayCastCallback in js and assign to
        // PxControllerDesc.reportCallback
        // https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html#deriving-from-c-classes-in-javascript
        class_<b2RayCastCallback>("b2RayCastCallback")
                .function("ReportFixture", &b2RayCastCallback::ReportFixture, pure_virtual(), allow_raw_pointers())
                .allow_subclass<b2RayCastCallbackWrapper>("b2RayCastCallbackWrapper", constructor<>());

        //binding class b2ContactListener
        class_<b2ContactListener>("ContactListener")
                .function("BeginContact", &b2ContactListener::BeginContact, allow_raw_pointers())
                .function("EndContact", &b2ContactListener::EndContact, allow_raw_pointers())
                .function("PreSolve", &b2ContactListener::PreSolve, allow_raw_pointers())
                .function("PostSolve", &b2ContactListener::PostSolve, allow_raw_pointers());

        //binding class b2Draw
        class_<b2Draw>("Draw")
                // .function("PushTransform", &b2Draw::PushTransform, allow_raw_pointers())
                // .function("PopTransform", &b2Draw::PopTransform, allow_raw_pointers())
                .function("DrawPolygon", &b2Draw::DrawPolygon, allow_raw_pointers())
                .function("DrawSolidPolygon", &b2Draw::DrawSolidPolygon, allow_raw_pointers())
                .function("DrawCircle", &b2Draw::DrawCircle, allow_raw_pointers())
                .function("DrawSolidCircle", &b2Draw::DrawSolidCircle, allow_raw_pointers())
                .function("DrawSegment", &b2Draw::DrawSegment, allow_raw_pointers())
                .function("DrawTransform", &b2Draw::DrawTransform, allow_raw_pointers())
                .function("DrawPoint", &b2Draw::DrawPoint, allow_raw_pointers())
                // .function("DrawString", &b2Draw::DrawString, allow_raw_pointers())
                // .function("DrawAABB", &b2Draw::DrawAABB, allow_raw_pointers())
                ;

        //binding class b2Contact
        class_<b2Contact>("Contact")
                // .function("GetManifold", &b2Contact::GetManifold)
                .function("GetWorldManifold", &b2Contact::GetWorldManifold, allow_raw_pointers())
                .function("IsTouching", &b2Contact::IsTouching)
                .function("SetEnabled", &b2Contact::SetEnabled)
                .function("IsEnabled", &b2Contact::IsEnabled)
                // .function("GetNext", &b2Contact::GetNext)
                // .function("GetFixtureA", &b2Contact::GetFixtureA)
                .function("GetChildIndexA", &b2Contact::GetChildIndexA)
                // .function("GetFixtureB", &b2Contact::GetFixtureB)
                .function("GetChildIndexB", &b2Contact::GetChildIndexB)
                .function("SetFriction", &b2Contact::SetFriction)
                .function("GetFriction", &b2Contact::GetFriction)
                .function("ResetFriction", &b2Contact::ResetFriction)
                .function("SetRestitution", &b2Contact::SetRestitution)
                .function("GetRestitution", &b2Contact::GetRestitution)
                .function("ResetRestitution", &b2Contact::ResetRestitution)
                .function("SetTangentSpeed", &b2Contact::SetTangentSpeed)
                .function("GetTangentSpeed", &b2Contact::GetTangentSpeed)
                .function("Evaluate", &b2Contact::Evaluate, allow_raw_pointers())
                ;

        //binding class b2World
        class_<b2World>("World")
                .constructor<b2Vec2>()
                .function("SetDestructionListener", &b2World::SetDestructionListener, allow_raw_pointers())
                .function("SetContactFilter", &b2World::SetContactFilter, allow_raw_pointers())
                .function("SetContactListener", &b2World::SetContactListener, allow_raw_pointers())
                .function("SetDebugDraw", &b2World::SetDebugDraw, allow_raw_pointers())
                .function("CreateBody", &b2World::CreateBody, allow_raw_pointers())
                .function("DestroyBody", &b2World::DestroyBody, allow_raw_pointers())
                .function("CreateJoint", &b2World::CreateJoint, allow_raw_pointers())
                .function("DestroyJoint", &b2World::DestroyJoint, allow_raw_pointers())
                .function("Step", &b2World::Step)
                .function("ClearForces", &b2World::ClearForces)
                // .function("DrawDebugData", &b2World::DrawDebugData)
                .function("QueryAABB", &b2World::QueryAABB, allow_raw_pointers())
                .function("RayCast", &b2World::RayCast, allow_raw_pointers())
                //.function("GetBodyList", &b2World::GetBodyList)
                .function("GetBodyList", optional_override([](b2World* f) {
                                if(f->GetBodyCount()) {
                                        return &(f->GetBodyList()[0]);
                                }else{
                                        return (b2Body*)nullptr;
                                }
                        }), allow_raw_pointers())
                // .function("GetJointList", &b2World::GetJointList)
                // .function("GetContactList", &b2World::GetContactList)
                .function("SetAllowSleeping", &b2World::SetAllowSleeping)
                .function("GetAllowSleeping", &b2World::GetAllowSleeping)
                .function("SetWarmStarting", &b2World::SetWarmStarting)
                .function("GetWarmStarting", &b2World::GetWarmStarting)
                .function("SetContinuousPhysics", &b2World::SetContinuousPhysics)
                .function("GetContinuousPhysics", &b2World::GetContinuousPhysics)
                .function("SetSubStepping", &b2World::SetSubStepping)
                .function("GetSubStepping", &b2World::GetSubStepping)
                .function("GetProxyCount", &b2World::GetProxyCount)
                .function("GetBodyCount", &b2World::GetBodyCount)
                .function("GetJointCount", &b2World::GetJointCount)
                .function("GetContactCount", &b2World::GetContactCount)
                .function("GetTreeHeight", &b2World::GetTreeHeight)
                .function("GetTreeBalance", &b2World::GetTreeBalance)
                .function("GetTreeQuality", &b2World::GetTreeQuality)
                .function("SetGravity", &b2World::SetGravity)
                .function("GetGravity", &b2World::GetGravity)
                .function("IsLocked", &b2World::IsLocked)
                .function("SetAutoClearForces", &b2World::SetAutoClearForces)
                .function("GetAutoClearForces", &b2World::GetAutoClearForces)
                .function("ShiftOrigin", &b2World::ShiftOrigin)
                .function("GetContactManager", &b2World::GetContactManager)
                .function("GetProfile", &b2World::GetProfile)
                .function("Dump", &b2World::Dump);


        //binding class b2Shape
        class_<b2Shape>("Shape")
                .property("m_type", &b2Shape::m_type)
                .property("m_radius", &b2Shape::m_radius)
                .function("GetType", &b2Shape::GetType)
                .function("GetChildCount", &b2Shape::GetChildCount)
                .function("TestPoint", &b2Shape::TestPoint)
                .function("RayCast", &b2Shape::RayCast, allow_raw_pointers())
                .function("ComputeAABB", &b2Shape::ComputeAABB, allow_raw_pointers())
                .function("ComputeMass", &b2Shape::ComputeMass, allow_raw_pointers())
                .function("SetRadius", optional_override([](b2Shape* f, float r) {
                        f->m_radius = r;
                        }), allow_raw_pointers())
                .function("GetRadius", optional_override([](b2Shape* f) {
                        return f->m_radius;
                        }), allow_raw_pointers())
                ;

        //binding class b2CircleShape
        class_<b2CircleShape, base<b2Shape>>("CircleShape")
                .constructor<>()
                .function("Clone", &b2CircleShape::Clone, allow_raw_pointers())
                .function("GetChildCount", &b2CircleShape::GetChildCount)
                .function("TestPoint", &b2CircleShape::TestPoint)
                .function("RayCast", &b2CircleShape::RayCast, allow_raw_pointers())
                .function("ComputeAABB", &b2CircleShape::ComputeAABB, allow_raw_pointers())
                .function("ComputeMass", &b2CircleShape::ComputeMass, allow_raw_pointers());

        //binding class b2EdgeShape
        class_<b2EdgeShape, base<b2Shape>>("EdgeShape")
                .function("Clone", &b2EdgeShape::Clone, allow_raw_pointers())
                .function("GetChildCount", &b2EdgeShape::GetChildCount)
                .function("TestPoint", &b2EdgeShape::TestPoint)
                .function("RayCast", &b2EdgeShape::RayCast, allow_raw_pointers())
                .function("ComputeAABB", &b2EdgeShape::ComputeAABB, allow_raw_pointers())
                .function("ComputeMass", &b2EdgeShape::ComputeMass, allow_raw_pointers());

        //binding class b2PolygonShape
        class_<b2PolygonShape, base<b2Shape>>("PolygonShape")
                .constructor<>()
                .function("Clone", &b2PolygonShape::Clone, allow_raw_pointers())
                .function("GetChildCount", &b2PolygonShape::GetChildCount)
                .function("TestPoint", &b2PolygonShape::TestPoint)
                .function("RayCast", &b2PolygonShape::RayCast, allow_raw_pointers())
                .function("ComputeAABB", &b2PolygonShape::ComputeAABB, allow_raw_pointers())
                .function("ComputeMass", &b2PolygonShape::ComputeMass, allow_raw_pointers())
                .function("Validate", &b2PolygonShape::Validate)
                .function("SetAsBox", select_overload<void(float, float)>(&b2PolygonShape::SetAsBox))
                .function("SetAsBoxWithCenterAndAngle", select_overload<void(float, float, const b2Vec2&, float)>(&b2PolygonShape::SetAsBox));


        //binding class b2FixtureDef
        class_<b2FixtureDef>("FixtureDef")
                .constructor<>()
                //.property("shape", &b2FixtureDef::getShape, &b2FixtureDef::setShape, allow_raw_pointers())
                .function("SetShape", optional_override([](b2FixtureDef* f, const b2Shape* s) {
                        f->shape = s;}), allow_raw_pointers())
                .function("GetShape", optional_override([](b2FixtureDef* f) {
                        return f->shape;}), allow_raw_pointers())
                .property("userData", &b2FixtureDef::userData)
                .property("friction", &b2FixtureDef::friction)
                .property("restitution", &b2FixtureDef::restitution)
                .property("density", &b2FixtureDef::density)
                .property("isSensor", &b2FixtureDef::isSensor)
                .property("filter", &b2FixtureDef::filter);

        //binding class b2Fixture
        class_<b2Fixture>("Fixture")
                .function("GetType", &b2Fixture::GetType)
                // .function("GetShape", &b2Fixture::GetShape)
                .function("SetSensor", &b2Fixture::SetSensor)
                .function("IsSensor", &b2Fixture::IsSensor)
                .function("SetFilterData", &b2Fixture::SetFilterData)
                .function("GetFilterData", &b2Fixture::GetFilterData)
                .function("Refilter", &b2Fixture::Refilter)
                // .function("GetBody", &b2Fixture::GetBody)
                // .function("GetNext", &b2Fixture::GetNext)
                // .function("GetUserData", &b2Fixture::GetUserData)
                // .function("SetUserData", &b2Fixture::SetUserData)
                .function("TestPoint", &b2Fixture::TestPoint)
                .function("RayCast", &b2Fixture::RayCast, allow_raw_pointers())
                .function("GetMassData", &b2Fixture::GetMassData, allow_raw_pointers())
                .function("SetDensity", &b2Fixture::SetDensity)
                .function("GetDensity", &b2Fixture::GetDensity)
                .function("GetFriction", &b2Fixture::GetFriction)
                .function("SetFriction", &b2Fixture::SetFriction)
                .function("GetRestitution", &b2Fixture::GetRestitution)
                .function("SetRestitution", &b2Fixture::SetRestitution)
                .function("GetAABB", &b2Fixture::GetAABB)
                .function("Dump", &b2Fixture::Dump);

        //bind b2BodyType
        enum_<b2BodyType>("BodyType")
                .value("b2_staticBody", b2_staticBody)
                .value("b2_kinematicBody", b2_kinematicBody)
                .value("b2_dynamicBody", b2_dynamicBody);

        //binding class b2BodyDef
        class_<b2BodyDef>("BodyDef")
                .constructor<>()
                .property("type", &b2BodyDef::type)
                .property("position", &b2BodyDef::position)
                .property("angle", &b2BodyDef::angle)
                .property("linearVelocity", &b2BodyDef::linearVelocity)
                .property("angularVelocity", &b2BodyDef::angularVelocity)
                .property("linearDamping", &b2BodyDef::linearDamping)
                .property("angularDamping", &b2BodyDef::angularDamping)
                .property("allowSleep", &b2BodyDef::allowSleep)
                .property("awake", &b2BodyDef::awake)
                .property("fixedRotation", &b2BodyDef::fixedRotation)
                .property("bullet", &b2BodyDef::bullet)
                //.property("userData", &b2BodyDef::userData)
                .property("gravityScale", &b2BodyDef::gravityScale);

        //binding class b2Body
        class_<b2Body>("Body")
                .function("CreateFixture", select_overload<b2Fixture*(const b2FixtureDef*)>(&b2Body::CreateFixture), allow_raw_pointers())
                // .function("CreateFixture", optional_override([](b2Body* body, const b2FixtureDef& f) {
                //         return body->CreateFixture(&f);
                //         }), allow_raw_pointers())
                .function("CreateFixtureWithShape", select_overload<b2Fixture*(const b2Shape*, float)>(&b2Body::CreateFixture), allow_raw_pointers())
                .function("DestroyFixture", &b2Body::DestroyFixture, allow_raw_pointers())
                .function("SetTransform", &b2Body::SetTransform)
                .function("GetTransform", &b2Body::GetTransform)
                .function("GetPosition", &b2Body::GetPosition)
                .function("GetAngle", &b2Body::GetAngle)
                .function("GetWorldCenter", &b2Body::GetWorldCenter)
                .function("GetLocalCenter", &b2Body::GetLocalCenter)
                .function("SetLinearVelocity", &b2Body::SetLinearVelocity)
                .function("GetLinearVelocity", &b2Body::GetLinearVelocity)
                .function("SetAngularVelocity", &b2Body::SetAngularVelocity)
                .function("GetAngularVelocity", &b2Body::GetAngularVelocity)
                .function("ApplyForce", &b2Body::ApplyForce)
                .function("ApplyForceToCenter", &b2Body::ApplyForceToCenter)
                .function("ApplyTorque", &b2Body::ApplyTorque)
                .function("ApplyLinearImpulse", &b2Body::ApplyLinearImpulse)
                .function("ApplyLinearImpulseToCenter", &b2Body::ApplyLinearImpulseToCenter)
                .function("ApplyAngularImpulse", &b2Body::ApplyAngularImpulse)
                .function("GetMass", &b2Body::GetMass)
                .function("GetInertia", &b2Body::GetInertia)
                .function("GetMassData", &b2Body::GetMassData)
                .function("SetMassData", &b2Body::SetMassData, allow_raw_pointers())
                .function("ResetMassData", &b2Body::ResetMassData)
                .function("GetWorldPoint", &b2Body::GetWorldPoint)
                .function("GetWorldVector", &b2Body::GetWorldVector)
                .function("GetLocalPoint", &b2Body::GetLocalPoint)
                .function("GetLocalVector", &b2Body::GetLocalVector)
                .function("GetLinearVelocityFromWorldPoint", &b2Body::GetLinearVelocityFromWorldPoint)
                .function("GetLinearVelocityFromLocalPoint", &b2Body::GetLinearVelocityFromLocalPoint)
                .function("GetLinearDamping", &b2Body::GetLinearDamping)
                .function("SetLinearDamping", &b2Body::SetLinearDamping)
                .function("GetAngularDamping", &b2Body::GetAngularDamping)
                .function("SetAngularDamping", &b2Body::SetAngularDamping)
                .function("GetGravityScale", &b2Body::GetGravityScale)
                .function("SetGravityScale", &b2Body::SetGravityScale)
                .function("SetType", &b2Body::SetType)
                .function("GetType", &b2Body::GetType)
                .function("SetBullet", &b2Body::SetBullet)
                .function("IsBullet", &b2Body::IsBullet)
                .function("SetSleepingAllowed", &b2Body::SetSleepingAllowed)
                .function("IsSleepingAllowed", &b2Body::IsSleepingAllowed)
                .function("SetAwake", &b2Body::SetAwake)
                .function("IsAwake", &b2Body::IsAwake)
                // .function("SetActive", &b2Body::SetActive)
                // .function("IsActive", &b2Body::IsActive)
                .function("SetFixedRotation", &b2Body::SetFixedRotation)
                .function("IsFixedRotation", &b2Body::IsFixedRotation)
                // .function("GetFixtureList", &b2Body::GetFixtureList)
                // .function("GetJointList", &b2Body::GetJointList)
                // .function("GetContactList", &b2Body::GetContactList)
                .function("GetNext", &b2Body::GetNext, allow_raw_pointers())
                // .function("GetUserData", &b2Body::GetUserData)
                // .function("SetUserData", &b2Body::SetUserData)
                .function("GetWorld", &b2Body::GetWorld, allow_raw_pointers())
                //.function("GetWorld", select_overload<const b2World*()>(&b2Body::GetWorld), allow_raw_pointers())
                .function("Dump", &b2Body::Dump);




        //binding class b2JointDef
        class_<b2JointDef>("JointDef")
                .constructor<>()
                .property("type", &b2JointDef::type)
                .property("userData", &b2JointDef::userData)
                //https://stackoverflow.com/questions/17056628/emscripten-error-when-binding-class-with-2d-double-array
                // .property("bodyA", &b2JointDef::bodyA, allow_raw_pointers())
                // .property("bodyB", &b2JointDef::bodyB, allow_raw_pointers())
                .function("SetBodyA", optional_override([](b2JointDef* j, b2Body* b) {
                        j->bodyA = b;}), allow_raw_pointers())
                .function("GetBodyA", optional_override([](b2JointDef* j) {
                        return j->bodyA;}), allow_raw_pointers())
                .function("SetBodyB", optional_override([](b2JointDef* j, b2Body* b) {
                        j->bodyB = b;}), allow_raw_pointers())
                .function("GetBodyB", optional_override([](b2JointDef* j) {
                        return j->bodyB;}), allow_raw_pointers())
                .property("collideConnected", &b2JointDef::collideConnected);

        //binding class b2DistanceJointDef
        class_<b2DistanceJointDef, base<b2JointDef>>("DistanceJointDef")
                .constructor<>()
                .property("localAnchorA", &b2DistanceJointDef::localAnchorA)
                .property("localAnchorB", &b2DistanceJointDef::localAnchorB)
                .property("length", &b2DistanceJointDef::length)
                .property("minLength", &b2DistanceJointDef::minLength)
                .property("maxLength", &b2DistanceJointDef::maxLength)
                .property("stiffness", &b2DistanceJointDef::stiffness)
                .property("damping", &b2DistanceJointDef::damping);

        //binding class b2WeldJointDef
        class_<b2WeldJointDef, base<b2JointDef>>("WeldJointDef")
                .constructor<>()
                .property("localAnchorA", &b2WeldJointDef::localAnchorA)
                .property("localAnchorB", &b2WeldJointDef::localAnchorB)
                .property("referenceAngle", &b2WeldJointDef::referenceAngle)
                .property("stiffness", &b2WeldJointDef::stiffness)
                .property("damping", &b2WeldJointDef::damping);

        //binding class b2RevoluteJointDef
        class_<b2RevoluteJointDef, base<b2JointDef>>("RevoluteJointDef")
                .constructor<>()
                .property("localAnchorA", &b2RevoluteJointDef::localAnchorA)
                .property("localAnchorB", &b2RevoluteJointDef::localAnchorB)
                .property("referenceAngle", &b2RevoluteJointDef::referenceAngle)
                .property("enableLimit", &b2RevoluteJointDef::enableLimit)
                .property("lowerAngle", &b2RevoluteJointDef::lowerAngle)
                .property("upperAngle", &b2RevoluteJointDef::upperAngle)
                .property("enableMotor", &b2RevoluteJointDef::enableMotor)
                .property("motorSpeed", &b2RevoluteJointDef::motorSpeed)
                .property("maxMotorTorque", &b2RevoluteJointDef::maxMotorTorque);
        

        //binding class b2Joint
        class_<b2Joint>("Joint")
                .function("GetType", &b2Joint::GetType)
                .function("GetBodyA", &b2Joint::GetBodyA, allow_raw_pointers())
                .function("GetBodyB", &b2Joint::GetBodyB, allow_raw_pointers())
                .function("GetAnchorA", &b2Joint::GetAnchorA, allow_raw_pointers())
                .function("GetAnchorB", &b2Joint::GetAnchorB, allow_raw_pointers())
                .function("GetReactionForce", &b2Joint::GetReactionForce)
                .function("GetReactionTorque", &b2Joint::GetReactionTorque)
                // .function("GetNext", &b2Joint::GetNext)
                // .function("GetUserData", &b2Joint::GetUserData)
                // .function("SetUserData", &b2Joint::SetUserData)
                // .function("IsActive", &b2Joint::IsActive)
                .function("GetCollideConnected", &b2Joint::GetCollideConnected)
                .function("Dump", &b2Joint::Dump);

        //binding class b2DistanceJoint
        class_<b2DistanceJoint, base<b2Joint>>("DistanceJoint")
                .function("GetLocalAnchorA", &b2DistanceJoint::GetLocalAnchorA)
                .function("GetLocalAnchorB", &b2DistanceJoint::GetLocalAnchorB)
                .function("SetLength", &b2DistanceJoint::SetLength)
                .function("GetLength", &b2DistanceJoint::GetLength)
                .function("SetMinLength", &b2DistanceJoint::SetMinLength)
                .function("GetMinLength", &b2DistanceJoint::GetMinLength)
                .function("SetMaxLength", &b2DistanceJoint::SetMaxLength)
                .function("GetMaxLength", &b2DistanceJoint::GetMaxLength)
                .function("SetStiffness", &b2DistanceJoint::SetStiffness)
                .function("GetStiffness", &b2DistanceJoint::GetStiffness)
                .function("SetDamping", &b2DistanceJoint::SetDamping)
                .function("GetDamping", &b2DistanceJoint::GetDamping)
                .function("Dump", &b2DistanceJoint::Dump);

        //binding class b2FrictionJoint
        class_<b2FrictionJoint, base<b2Joint>>("FrictionJoint")
                .function("GetLocalAnchorA", &b2FrictionJoint::GetLocalAnchorA)
                .function("GetLocalAnchorB", &b2FrictionJoint::GetLocalAnchorB)
                .function("SetMaxForce", &b2FrictionJoint::SetMaxForce)
                .function("GetMaxForce", &b2FrictionJoint::GetMaxForce)
                .function("SetMaxTorque", &b2FrictionJoint::SetMaxTorque)
                .function("GetMaxTorque", &b2FrictionJoint::GetMaxTorque)
                .function("Dump", &b2FrictionJoint::Dump);

        //binding class b2GearJoint
        class_<b2GearJoint, base<b2Joint>>("GearJoint")
                .function("GetJoint1", &b2GearJoint::GetJoint1, allow_raw_pointers())
                .function("GetJoint2", &b2GearJoint::GetJoint2, allow_raw_pointers())
                .function("SetRatio", &b2GearJoint::SetRatio)
                .function("GetRatio", &b2GearJoint::GetRatio)
                .function("Dump", &b2GearJoint::Dump);

        //binding class b2MotorJoint
        class_<b2MotorJoint, base<b2Joint>>("MotorJoint")
                .function("SetLinearOffset", &b2MotorJoint::SetLinearOffset)
                .function("GetLinearOffset", &b2MotorJoint::GetLinearOffset)
                .function("SetAngularOffset", &b2MotorJoint::SetAngularOffset)
                .function("GetAngularOffset", &b2MotorJoint::GetAngularOffset)
                .function("SetMaxForce", &b2MotorJoint::SetMaxForce)
                .function("GetMaxForce", &b2MotorJoint::GetMaxForce)
                .function("SetMaxTorque", &b2MotorJoint::SetMaxTorque)
                .function("GetMaxTorque", &b2MotorJoint::GetMaxTorque)
                .function("SetCorrectionFactor", &b2MotorJoint::SetCorrectionFactor)
                .function("GetCorrectionFactor", &b2MotorJoint::GetCorrectionFactor)
                .function("Dump", &b2MotorJoint::Dump);

        //binding class b2MouseJoint
        class_<b2MouseJoint, base<b2Joint>>("MouseJoint")
                .function("SetTarget", &b2MouseJoint::SetTarget)
                .function("GetTarget", &b2MouseJoint::GetTarget)
                .function("SetMaxForce", &b2MouseJoint::SetMaxForce)
                .function("GetMaxForce", &b2MouseJoint::GetMaxForce)
                .function("SetStiffness", &b2MouseJoint::SetStiffness)
                .function("GetStiffness", &b2MouseJoint::GetStiffness)
                .function("SetDamping", &b2MouseJoint::SetDamping)
                .function("GetDamping", &b2MouseJoint::GetDamping)
                .function("Dump", &b2MouseJoint::Dump);

        //binding class b2PrismaticJoint
        class_<b2PrismaticJoint, base<b2Joint>>("PrismaticJoint")
                .function("GetLocalAnchorA", &b2PrismaticJoint::GetLocalAnchorA)
                .function("GetLocalAnchorB", &b2PrismaticJoint::GetLocalAnchorB)
                .function("GetLocalAxisA", &b2PrismaticJoint::GetLocalAxisA)
                .function("GetReferenceAngle", &b2PrismaticJoint::GetReferenceAngle)
                .function("GetJointTranslation", &b2PrismaticJoint::GetJointTranslation)
                .function("GetJointSpeed", &b2PrismaticJoint::GetJointSpeed)
                .function("IsLimitEnabled", &b2PrismaticJoint::IsLimitEnabled)
                .function("EnableLimit", &b2PrismaticJoint::EnableLimit)
                .function("GetLowerLimit", &b2PrismaticJoint::GetLowerLimit)
                .function("GetUpperLimit", &b2PrismaticJoint::GetUpperLimit)
                .function("SetLimits", &b2PrismaticJoint::SetLimits)
                .function("IsMotorEnabled", &b2PrismaticJoint::IsMotorEnabled)
                .function("EnableMotor", &b2PrismaticJoint::EnableMotor)
                .function("SetMotorSpeed", &b2PrismaticJoint::SetMotorSpeed)
                .function("GetMotorSpeed", &b2PrismaticJoint::GetMotorSpeed)
                .function("SetMaxMotorForce", &b2PrismaticJoint::SetMaxMotorForce)
                .function("GetMaxMotorForce", &b2PrismaticJoint::GetMaxMotorForce)
                .function("GetMotorForce", &b2PrismaticJoint::GetMotorForce)
                .function("Dump", &b2PrismaticJoint::Dump);

        //binding class b2PulleyJoint
        class_<b2PulleyJoint, base<b2Joint>>("PulleyJoint")
                .function("GetGroundAnchorA", &b2PulleyJoint::GetGroundAnchorA)
                .function("GetGroundAnchorB", &b2PulleyJoint::GetGroundAnchorB)
                .function("GetLengthA", &b2PulleyJoint::GetLengthA)
                .function("GetLengthB", &b2PulleyJoint::GetLengthB)
                .function("GetRatio", &b2PulleyJoint::GetRatio)
                .function("GetCurrentLengthA", &b2PulleyJoint::GetCurrentLengthA)
                .function("GetCurrentLengthB", &b2PulleyJoint::GetCurrentLengthB)
                .function("Dump", &b2PulleyJoint::Dump);

        //binding class b2RevoluteJoint
        class_<b2RevoluteJoint, base<b2Joint>>("RevoluteJoint")
                .function("GetLocalAnchorA", &b2RevoluteJoint::GetLocalAnchorA)
                .function("GetLocalAnchorB", &b2RevoluteJoint::GetLocalAnchorB)
                .function("GetReferenceAngle", &b2RevoluteJoint::GetReferenceAngle)
                .function("GetJointAngle", &b2RevoluteJoint::GetJointAngle)
                .function("GetJointSpeed", &b2RevoluteJoint::GetJointSpeed)
                .function("IsLimitEnabled", &b2RevoluteJoint::IsLimitEnabled)
                .function("EnableLimit", &b2RevoluteJoint::EnableLimit)
                .function("GetLowerLimit", &b2RevoluteJoint::GetLowerLimit)
                .function("GetUpperLimit", &b2RevoluteJoint::GetUpperLimit)
                .function("SetLimits", &b2RevoluteJoint::SetLimits)
                .function("IsMotorEnabled", &b2RevoluteJoint::IsMotorEnabled)
                .function("EnableMotor", &b2RevoluteJoint::EnableMotor)
                .function("SetMotorSpeed", &b2RevoluteJoint::SetMotorSpeed)
                .function("GetMotorSpeed", &b2RevoluteJoint::GetMotorSpeed)
                .function("SetMaxMotorTorque", &b2RevoluteJoint::SetMaxMotorTorque)
                .function("GetMaxMotorTorque", &b2RevoluteJoint::GetMaxMotorTorque)
                .function("GetMotorTorque", &b2RevoluteJoint::GetMotorTorque)
                .function("Dump", &b2RevoluteJoint::Dump);

        //binding class b2WeldJoint
        class_<b2WeldJoint, base<b2Joint>>("WeldJoint")
                .function("GetLocalAnchorA", &b2WeldJoint::GetLocalAnchorA)
                .function("GetLocalAnchorB", &b2WeldJoint::GetLocalAnchorB)
                .function("GetReferenceAngle", &b2WeldJoint::GetReferenceAngle)
                .function("SetStiffness", &b2WeldJoint::SetStiffness)
                .function("GetStiffness", &b2WeldJoint::GetStiffness)
                .function("SetDamping", &b2WeldJoint::SetDamping)
                .function("GetDamping", &b2WeldJoint::GetDamping)
                .function("Dump", &b2WeldJoint::Dump);

        //binding class b2WheelJoint
        class_<b2WheelJoint, base<b2Joint>>("WheelJoint")
                .function("GetLocalAnchorA", &b2WheelJoint::GetLocalAnchorA)
                .function("GetLocalAnchorB", &b2WheelJoint::GetLocalAnchorB)
                .function("GetLocalAxisA", &b2WheelJoint::GetLocalAxisA)
                .function("GetJointTranslation", &b2WheelJoint::GetJointTranslation)
                // .function("GetJointSpeed", &b2WheelJoint::GetJointSpeed)
                .function("IsMotorEnabled", &b2WheelJoint::IsMotorEnabled)
                .function("EnableMotor", &b2WheelJoint::EnableMotor)
                .function("SetMotorSpeed", &b2WheelJoint::SetMotorSpeed)
                .function("GetMotorSpeed", &b2WheelJoint::GetMotorSpeed)
                .function("SetMaxMotorTorque", &b2WheelJoint::SetMaxMotorTorque)
                .function("GetMaxMotorTorque", &b2WheelJoint::GetMaxMotorTorque)
                .function("GetMotorTorque", &b2WheelJoint::GetMotorTorque)
                .function("SetStiffness", &b2WheelJoint::SetStiffness)
                .function("GetStiffness", &b2WheelJoint::GetStiffness)
                .function("SetDamping", &b2WheelJoint::SetDamping)
                .function("GetDamping", &b2WheelJoint::GetDamping)
                .function("Dump", &b2WheelJoint::Dump);

        // //binding class RopeJoint
        // class_<b2RopeJoint, base<b2Joint>>("RopeJoint")
        //         .function("GetLocalAnchorA", &b2RopeJoint::GetLocalAnchorA)
        //         .function("GetLocalAnchorB", &b2RopeJoint::GetLocalAnchorB)
        //         .function("SetMaxLength", &b2RopeJoint::SetMaxLength)
        //         .function("GetMaxLength", &b2RopeJoint::GetMaxLength)
        //         .function("GetLimitState", &b2RopeJoint::GetLimitState)
        //         .function("Dump", &b2RopeJoint::Dump);



        }


        namespace emscripten {
        namespace internal {
        // Physx uses private destructors all over the place for its own reference
        // counting embind doesn't deal with this well, so we have to override the
        // destructors to keep them private in the bindings See:
        // https://github.com/emscripten-core/emscripten/issues/5587
        template <> void raw_destructor<b2Contact>(b2Contact *) {}
        template <> void raw_destructor<b2Shape>(b2Shape *) {}
        template <> void raw_destructor<b2CircleShape>(b2CircleShape *) {}
        template <> void raw_destructor<b2EdgeShape>(b2EdgeShape *) {}
        template <> void raw_destructor<b2PolygonShape>(b2PolygonShape *) {}
        template <> void raw_destructor<b2BodyDef>(b2BodyDef *) {}
        template <> void raw_destructor<b2Body>(b2Body *) {}
        template <> void raw_destructor<b2Fixture>(b2Fixture *) {}
        template <> void raw_destructor<b2Joint>(b2Joint *) {}
        template <> void raw_destructor<b2DistanceJoint>(b2DistanceJoint *) {}
        template <> void raw_destructor<b2FrictionJoint>(b2FrictionJoint *) {}
        template <> void raw_destructor<b2GearJoint>(b2GearJoint *) {}
        template <> void raw_destructor<b2MotorJoint>(b2MotorJoint *) {}
        template <> void raw_destructor<b2MouseJoint>(b2MouseJoint *) {}
        template <> void raw_destructor<b2PrismaticJoint>(b2PrismaticJoint *) {}
        template <> void raw_destructor<b2PulleyJoint>(b2PulleyJoint *) {}
        template <> void raw_destructor<b2RevoluteJoint>(b2RevoluteJoint *) {}
        template <> void raw_destructor<b2WeldJoint>(b2WeldJoint *) {}
        template <> void raw_destructor<b2WheelJoint>(b2WheelJoint *) {}
        // template <> void raw_destructor<b2World>(b2World *) {}

        } // namespace internal
        } // namespace emscripten
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

const int MAX_THRUST = 100;
const int MIN_THRUST = 0;

struct Checkpoint {
  int x;
  int y;
  int distance;
  int angle;
};

class PodController {
private:
    bool canUseBoost_;
    bool checkpointsCompleted_;
    double distanceThreshold_;
    double currMaxCPDistance_;
    int checkpointCount_;

    Checkpoint prevCheckpoint_;
    Checkpoint checkpointForBoost_;
    map<int, Checkpoint> checkpoints;
public:
    PodController(const double& minDist = 0.3) {
        distanceThreshold_ = minDist;
        canUseBoost_ = true;
        checkpointsCompleted_ = false;
        checkpointForBoost_ = {0, 0, 0, 0};
        checkpointCount_ = 0;
        currMaxCPDistance_ = 0.;
        prevCheckpoint_ = {0, 0, 0, 0};
    }

    void manageControllerState(const Checkpoint& checkpoint) {

        bool newCheckpoint = checkpoint.x != prevCheckpoint_.x || checkpoint.y != prevCheckpoint_.y;

        if (newCheckpoint && !checkpointsCompleted_) {
            for (const auto& cp : checkpoints) {
                if (cp.second.x == checkpoint.x && cp.second.y == checkpoint.y) {
                    checkpointsCompleted_ = true;
                    currMaxCPDistance_ = checkpoint.distance;
                    return;
                }
            }      

            if(checkpoint.distance > checkpointForBoost_.distance) {
                checkpointForBoost_ = checkpoint;
            }
            
            checkpointCount_++;
            checkpoints[checkpointCount_] = checkpoint;
            currMaxCPDistance_ = checkpoint.distance;
        } else if (newCheckpoint && checkpointsCompleted_) {
            currMaxCPDistance_ = checkpoint.distance;
        }

        prevCheckpoint_ = checkpoint;
    }

    int calculateOptimalThrust(const Checkpoint& checkpoint) {
        manageControllerState(checkpoint);

        const int maxThrust = MAX_THRUST;
        const int minThrust = MIN_THRUST;

        const double normDistance = checkpoint.distance / currMaxCPDistance_;

        if (normDistance < distanceThreshold_) {
            double thrust = maxThrust * (1 - 0.3 * abs(checkpoint.angle) / 180.0) * (1 - normDistance);
            thrust = std::round(thrust);
            thrust = std::max(thrust, static_cast<double>(minThrust));
            thrust = std::min(thrust, static_cast<double>(maxThrust));
            return thrust;
        }

        return maxThrust;
    }

    bool determineOptimalBoostUsage(const Checkpoint& checkpoint) {
        bool maxAngle = abs(checkpoint.angle) <= 3;
        bool isCheckpointForBoost = checkpointForBoost_.x == checkpoint.x && checkpointForBoost_.y == checkpoint.y;
        if(checkpointsCompleted_ && canUseBoost_ && isCheckpointForBoost && maxAngle) {
            canUseBoost_ = false;
            return true;
        }
        return false;
    }
};

int main()
{
    PodController podController;

    while (true) {
        int x;
        int y;
        Checkpoint checkpoint;

        cin >> x >> y >> checkpoint.x >> checkpoint.y >> checkpoint.distance >> checkpoint.angle; cin.ignore();

        int opponentX;
        int opponentY;

        cin >> opponentX >> opponentY; cin.ignore();

        bool boost = podController.determineOptimalBoostUsage(checkpoint);
        if(boost) {
            cout << checkpoint.x << " " << checkpoint.y << " " << "BOOST" << endl;
        } else {
            int thrust = 0;
            if(checkpoint.angle > 90 || checkpoint.angle < -90) {
                thrust = 0;
            } else {
                thrust = podController.calculateOptimalThrust(checkpoint);
            }
            cout << checkpoint.x << " " << checkpoint.y << " " << thrust << endl;
        }
    }
}

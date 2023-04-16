# map_pod_racing

This code uses the class PodController to manage the pod's state and determine the optimal thrust required to reach the next checkpoint.

The PodController class maintains a list of checkpoints that the pod must traverse. The manageControllerState function manages the pod's progress through the checkpoints, updates the state, and determines if the pod can use a boost.

The calculateOptimalThrust function determines the optimal thrust required for the pod to reach the next checkpoint. It takes the distance and angle to the next checkpoint and returns the optimal thrust required.

The determineOptimalBoostUsage function determines if the pod should use the boost. It checks if the pod has passed all the checkpoints, if the boost is available, if the pod is close to a checkpoint where the boost can be used, and if the angle to the next checkpoint is within a certain threshold.

The main function reads in the input from the problem statement and uses the PodController class to determine the pod's next move. If the boost can be used, it prints BOOST. Otherwise, it prints the optimal thrust required to reach the next checkpoint.
